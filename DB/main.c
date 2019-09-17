#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


//管理进程的命令，以'.'开头，如.exit
typedef enum
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED
} MetaCommandResult;

//为命令的执行作准备，检查参数合法性等。
typedef enum
{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED,
    PREPARE_SYNTAX_ERROR,
    PREPARE_STRING_TOO_LONG,
    PREPARE_NEGATIVE_ID
} PrepareResult;

//命令执行结果
typedef enum
{
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL,
    EXECUTE_FAIL
} ExecuteResult;

//命令类型
typedef enum
{
    STATEMENT_INSERT, STATEMENT_SELECT
} StatementType;

typedef void (*PFunc)(void* arg1, void* arg2);

typedef struct 
{
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

//命令结构体
typedef struct 
{
    char* cmd_name;
    PFunc cmd_func;
    int cmd_num;
} Command;

//最大名称长度
#define COLUME_USERNAME_SIZE 32
//最大email长度
#define COLUME_EMAIL_SIZE 255

//数据库表中每一行存储的内容
typedef struct 
{
    uint32_t id;
    //以'\0'结尾，所以要+1
    char username[COLUME_USERNAME_SIZE+1];
    char email[COLUME_EMAIL_SIZE+1];
} Row;


typedef struct 
{
    StatementType type;
    Row row_to_insert;
} Statement;

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

#define ID_SIZE size_of_attribute(Row, id)
#define USERNAME_SIZE size_of_attribute(Row, username)
#define EMAIL_SIZE size_of_attribute(Row, email)
#define ID_OFFSET 0
#define USERNAME_OFFSET (ID_OFFSET + ID_SIZE)
#define EMAIL_OFFSET (USERNAME_OFFSET + USERNAME_SIZE)
#define ROW_SIZE (ID_SIZE + USERNAME_SIZE + EMAIL_SIZE)

//序列化行，即将输入的行信息存入数据库表中的某一行
void serialize_row(Row* source, void* destination)
{
    memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
    memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
    memcpy(destination + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

//反序列化行，将数据库表中的某一行的信息取出
void deserialize_row(void* source, Row* destination)
{
    memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
    memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}

//数据库中每一页的字节数
#define PAGE_SIZE 4096
//数据库表中最大页数
#define TABLE_MAX_PAGES 100
//每一页中的行数
//#define ROWS_PER_PAGE (PAGE_SIZE / ROW_SIZE)
//数据库表中最多能存储的行数
//#define TABLE_MAX_ROWS (ROWS_PER_PAGE * TABLE_MAX_PAGES)

//pager结构体
typedef struct 
{
    int file_descriptor;
    uint32_t file_length;
    uint32_t num_pages;
    void* pages[TABLE_MAX_PAGES];
} Pager;

//数据库表结构
typedef struct 
{
    uint32_t root_page_num;
    Pager* pager;
} Table;

typedef struct
{
    Table* table;
    uint32_t page_num;
    uint32_t cell_num;
    bool end_of_table;
} Cursor;

typedef enum{NODE_INTERNAL, NODE_LEAF} NodeType;

// common node header
#define NODE_TYPE_SIZE sizeof(uint8_t)
#define NODE_TYPE_OFFSET 0
#define IS_ROOT_SIZE sizeof(uint8_t)
#define IS_ROOT_OFFSET NODE_TYPE_SIZE
#define PARENT_POINTER_SIZE sizeof(uint32_t)
#define PARENT_POINTER_OFFSET (IS_ROOT_OFFSET + PARENT_POINTER_SIZE)
#define COMMON_NODE_HEADER_SIZE (NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE)

// leaf node header
#define LEAF_NODE_NUM_CELLS_SIZE sizeof(uint32_t)
#define LEAF_NODE_NUM_CELLS_OFFSET (COMMON_NODE_HEADER_SIZE + LEAF_NODE_NUM_CELLS_SIZE)
#define LEAF_NODE_HEADER_SIZE (COMMON_NODE_HEADER_SIZE + LEAF_NODE_NUM_CELLS_SIZE)

//leaf node body
#define LEAF_NODE_KEY_SIZE sizeof(uint32_t)
#define LEAF_NODE_KEY_OFFSET 0
#define LEAF_NODE_VALUE_SIZE ROW_SIZE
#define LEAF_NODE_VALUE_OFFSET (LEAF_NODE_KEY_OFFSET + LEAF_NODE_KEY_SIZE)
#define LEAF_NODE_CELL_SIZE (LEAF_NODE_KEY_SIZE + LEAF_NODE_VALUE_SIZE)
#define LEAF_NODE_SPACE_FOR_CELLS (PAGE_SIZE - LEAF_NODE_HEADER_SIZE)
#define LEAF_NODE_MAX_CELLS (LEAF_NODE_SPACE_FOR_CELLS / LEAF_NODE_CELL_SIZE)


void* get_page(Pager* pager, uint32_t page_num)
{
    if(page_num >= TABLE_MAX_PAGES)
    {
        printf("page number out of bounds.");
        exit(EXIT_FAILURE);
    }
    if(pager->pages[page_num] == NULL)
    {
        void* page = (void*) malloc(PAGE_SIZE);
        uint32_t num_pages = pager->file_length / PAGE_SIZE;

        if(pager->file_length % PAGE_SIZE)
        {
            num_pages += 1;
        }

        if(page_num <= num_pages)
        {
            lseek(pager->file_descriptor, num_pages * PAGE_SIZE, SEEK_SET);
            ssize_t bytes_read = read(pager->file_descriptor, page, PAGE_SIZE);

            if(bytes_read == -1)
            {
                printf("read page failed.");
                exit(EXIT_FAILURE);
            }
        }

        pager->pages[page_num] = page;

        if(page_num >= pager->num_pages)
        {
            pager->num_pages = page_num + 1;
        }
    }

    return pager->pages[page_num];
}

uint32_t* leaf_node_num_cells(void* node)
{
    return node + LEAF_NODE_NUM_CELLS_OFFSET;
}

void* leaf_node_cell(void* node, uint32_t cell_num)
{
    return node + LEAF_NODE_HEADER_SIZE + cell_num * LEAF_NODE_CELL_SIZE;
}

uint32_t* leaf_node_key(void* node, uint32_t cell_num)
{
    return leaf_node_cell(node, cell_num);
}

void* leaf_node_value(void* node, uint32_t cell_num)
{
    return leaf_node_cell(node, cell_num) + LEAF_NODE_KEY_SIZE;
}

void initialize_leaf_node(void* node)
{
    *leaf_node_num_cells(node) = 0;
}

void leaf_node_insert(Cursor* cursor, uint32_t key, Row* value)
{
    void* node = get_page(cursor->table->pager, cursor->page_num);

    uint32_t num_cells = leaf_node_num_cells(node);
    if(num_cells >= LEAF_NODE_MAX_CELLS)
    {
        printf("node is full, can not insert.");
        exit(EXIT_FAILURE);
    }

    uint32_t cell_num = cursor->cell_num;
    if(cell_num >= LEAF_NODE_MAX_CELLS || cell_num < 0)
    {
        printf("cell num of cursor out of bounds.");
        exit(EXIT_FAILURE);
    }

    if(cell_num < num_cells)
    {
        for (size_t i = num_cells; i > cell_num ; i--)
        {
            memcpy(leaf_node_cell(node, i), leaf_node_cell(node, i-1), LEAF_NODE_CELL_SIZE);
        }
    }

    *leaf_node_num_cells(node) += 1;
    *leaf_node_key(node, cell_num) = key;
    serialize_row(value, leaf_node_value(node, cell_num));
}

Cursor* table_start(Table* table)
{
    Cursor* cursor = malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->page_num = table->root_page_num;
    cursor->cell_num = 0;

    void* root_node = get_page(table->pager, table->root_page_num);
    uint32_t num_cells = leaf_node_num_cells(root_node);
    cursor->end_of_table = num_cells == 0;

    return cursor;
}

Cursor* table_end(Table* table)
{
    Cursor* cursor = malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->page_num = table->root_page_num;
    
    void* root_node = get_page(table->pager, table->root_page_num);
    uint32_t num_cells = leaf_node_num_cells(root_node);
    cursor->cell_num = num_cells;
    cursor->end_of_table = true;

    return cursor;
}

void cursor_advance(Cursor* cursor)
{
    uint32_t page_num = cursor->page_num;
    void* node = get_page(cursor->table->pager, page_num);
    
    cursor->cell_num += 1;
    if(cursor->cell_num >= (*leaf_node_num_cells(node)))
    {
        cursor->end_of_table = true;
    }
}

//获取将要执行操作的行指针
void * cursor_value(Cursor* cursor)
{
    uint32_t page_num = cursor->page_num;
    void* page = get_page(cursor->table->pager, page_num);
    return leaf_node_value(page, cursor->cell_num);
}

void page_fill(Pager* pager, uint32_t page_num)
{
    if(page_num > TABLE_MAX_PAGES)
    {
        printf("page number out of bounds.");
        exit(EXIT_FAILURE);
    }

    if(pager->pages[page_num] == NULL)
    {
        void* page = (void*) malloc(PAGE_SIZE);
        lseek(pager->file_descriptor, page_num * PAGE_SIZE, SEEK_SET);
        ssize_t bytes_read = read(pager->file_descriptor, page, PAGE_SIZE);

        if(bytes_read == -1)
        {
            printf("read page failed.\n");
            exit(EXIT_FAILURE);
        }

        pager->pages[page_num] = page;
    }
}

Pager* pager_open(const char* filename)
{
    int fd = open(filename, O_RDWR | O_CREAT);
    if(fd == -1)
    {
        printf("open file failed %s", filename);
        exit(EXIT_FAILURE);
    }

    off_t file_length = lseek(fd, 0, SEEK_END);

    Pager* pager = (Pager*) malloc(sizeof(Pager));
    pager->file_descriptor = fd;
    pager->file_length = file_length;
    pager->num_pages = file_length / PAGE_SIZE;

    if(file_length % PAGE_SIZE != 0)
    {
        printf("db file is not a whole number of pages.");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<TABLE_MAX_PAGES;i++)
    {
        pager->pages[i] = NULL;
    }

    for(int i=0;i<pager->num_pages;i++)
    {
        printf("get page %d\n", i);
        page_fill(pager, i);
    }

    return pager;
}

Table* db_open(const char* filename)
{
    Pager* pager = pager_open(filename);

    Table* table = (Table*) malloc(sizeof(Table));
    table->root_page_num = 0;
    table->pager = pager;

    if(pager->num_pages == 0)
    {
        void* root_node = get_page(pager, table->root_page_num);
        initialize_leaf_node(root_node);
    }

    return table;
}

void page_flush(Pager* pager, uint32_t page_num)
{
    if(page_num >= TABLE_MAX_PAGES)
    {
        printf("page num out of bounds.");
        exit(EXIT_FAILURE);
    }

    void* page = pager->pages[page_num];
    if(page == NULL)
    {
        return;
    }

    uint32_t bytes_offset = page_num * PAGE_SIZE;
    off_t offset = lseek(pager->file_descriptor, bytes_offset, SEEK_SET);
    if(offset == -1)
    {
        printf("error seeking.");
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_write = write(pager->file_descriptor, page, PAGE_SIZE);
    if(bytes_write == -1)
    {
        printf("page flush failed.");
        exit(EXIT_FAILURE);
    }
}

void db_close(Table* table)
{
    Pager* pager = table->pager;

    for(uint32_t i=0;i<pager->num_pages;i++)
    {
        void* page = pager->pages[i];
        if(page != NULL)
        {
            page_flush(pager, i);
            free(page);
            pager->pages[i] = NULL;
        }
    }

    for(int i=0;i<TABLE_MAX_PAGES;i++)
    {
        void* page = pager->pages[i];
        if(page != NULL)
        {
            free(page);
            pager->pages[i] = NULL;
        }
    }

    free(pager);
    free(table);

    int result = close(pager->file_descriptor);
    if(result == -1)
    {
        printf("close database file failed.");
        exit(EXIT_FAILURE);
    }
}

//分配input buffer
InputBuffer* new_input_buffer()
{
	InputBuffer* inputbuffer = (InputBuffer*) malloc(sizeof(InputBuffer));
	inputbuffer->buffer = NULL;
	inputbuffer->buffer_length = 0;
	inputbuffer->input_length = 0;

	return inputbuffer;
}

//打印提示符
void print_prompt()
{
    printf("db > ");
}

//去掉字符串前后的空格
void trim(char** text, size_t length)
{
    if(text == NULL || length == 0)
        return;

    char* start = *text;
    while(*start++ == ' ');
    start--;
    char* end = *text + length - 1;
    while(*end-- == ' ');
    end++;

    size_t pos = 0;
    for(char* c=start;c<=end;c++)
    {
        (*text)[pos++] = *c;
    }
    (*text)[pos] = '\0';
}

//读取输入
void read_input(InputBuffer* inputbuffer)
{
    ssize_t bytes_read = getline(&(inputbuffer->buffer), &(inputbuffer->buffer_length), stdin);

    if(bytes_read <=0)
    {
        printf("no input read\n");
        exit(EXIT_FAILURE);
    }

    inputbuffer->input_length = bytes_read - 1;
    inputbuffer->buffer[bytes_read - 1] = 0;
    trim(&inputbuffer->buffer, inputbuffer->input_length);
}

//释放输入缓冲
void close_inputbuffer(InputBuffer* inputbuffer)
{
    free(inputbuffer->buffer);
    free(inputbuffer);
}

void print_constants() 
{
    printf("ROW_SIZE: %ld\n", ROW_SIZE);
    printf("COMMON_NODE_HEADER_SIZE: %d\n", COMMON_NODE_HEADER_SIZE);
    printf("LEAF_NODE_HEADER_SIZE: %d\n", LEAF_NODE_HEADER_SIZE);
    printf("LEAF_NODE_CELL_SIZE: %d\n", LEAF_NODE_CELL_SIZE);
    printf("LEAF_NODE_SPACE_FOR_CELLS: %d\n", LEAF_NODE_SPACE_FOR_CELLS);
    printf("LEAF_NODE_MAX_CELLS: %d\n", LEAF_NODE_MAX_CELLS);
}

void print_leaf_node(void* node) 
{
    uint32_t num_cells = *leaf_node_num_cells(node);
    printf("leaf (size %d)\n", num_cells);

    for (uint32_t i = 0; i < num_cells; i++) 
    {
        uint32_t key = *leaf_node_key(node, i);
        printf("  - %d : %d\n", i, key);
    }
}

//退出进程
void db_exit(void* arg1, void* arg2)
{
    InputBuffer* inputbuffer = (InputBuffer*) arg1;
    close_inputbuffer(inputbuffer);

    Table* table = (Table*) arg2;
    db_close(table);

    printf("exit db\n");
    exit(EXIT_SUCCESS);
}

void db_show(void* arg1, void* arg2)
{
    printf("call show func\n");
}

void db_const(void* arg1, void* arg2)
{
    printf("Constants:\n");
    print_constants();
}

void db_btree(void* arg1, void* arg2)
{
    printf("Tree:\n");
    Table* table = (Table*) arg2;
    print_leaf_node(get_page(table->pager, 0));
}

//命令数组
Command cmds[]=
{
    {
        ".exit", db_exit, 1
    },
    {
        ".show", db_show, 1
    },
    {
        ".const", db_const, 1
    },
    {
        ".btree", db_btree, 1
    },
    {
        NULL, NULL, 0
    }
};

//根据命令名称查找需要执行的命令
PFunc find_func(char* cmd_name)
{
    Command* cmd;
    for(cmd = &cmds[0];cmd->cmd_num;cmd++)
    {
        if(strcmp(cmd_name, cmd->cmd_name) == 0)
        {
            return cmd->cmd_func;
        }
    }

    return NULL;
}

//执行元命令
MetaCommandResult do_meta_command(InputBuffer* inputbuffer, Table* table)
{
    PFunc func = find_func(inputbuffer->buffer);
    if(func != NULL)
    {
        func(inputbuffer, table);
        return META_COMMAND_SUCCESS;
    }
    return META_COMMAND_UNRECOGNIZED;
}

//为执行插入命令做准备
PrepareResult prepare_insert(InputBuffer* inputbuffer, Statement* statement)
{
    statement->type = STATEMENT_INSERT;

    char* keyword = strtok(inputbuffer->buffer, " ");
    char* id_string = strtok(NULL, " ");
    char* username = strtok(NULL, " ");
    char* email = strtok(NULL, " ");

    if(id_string == NULL || username == NULL || email == NULL)
    {
        return PREPARE_SYNTAX_ERROR;
    }

    if(strlen(username) > COLUME_USERNAME_SIZE)
    {
        return PREPARE_STRING_TOO_LONG;
    }
    if(strlen(email) > COLUME_EMAIL_SIZE)
    {
        return PREPARE_STRING_TOO_LONG;
    }

    int id = atoi(id_string);
    if(id < 0)
    {
        return PREPARE_NEGATIVE_ID;
    }

    statement->row_to_insert.id = id;
    strcpy(statement->row_to_insert.username, username);
    strcpy(statement->row_to_insert.email, email);

    return PREPARE_SUCCESS;
}

//为执行命令作准备
PrepareResult prepare_statement(InputBuffer* inputbuffer, Statement* statement)
{
    if(strncmp(inputbuffer->buffer, "insert", 6) == 0)
    {
        return prepare_insert(inputbuffer, statement);
    }
    if(strncmp(inputbuffer->buffer, "select", 6) == 0)
    {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED;
}

//打印行信息
void print_row(Row* row)
{
    printf("row info : id %d. username %s. email %s.\n", row->id, row->username, row->email);
}

//执行插入命令
ExecuteResult execute_insert(Statement* statement, Table* table)
{
    void* node = get_page(table->pager, table->root_page_num);
    if(*leaf_node_num_cells(node) >= LEAF_NODE_MAX_CELLS)
    {
        return EXECUTE_TABLE_FULL;
    }

    Cursor* cursor = table_end(table);
    Row* row_to_insert = &(statement->row_to_insert);
    leaf_node_insert(cursor, row_to_insert->id, row_to_insert);

    free(cursor);

    return EXECUTE_SUCCESS;
}

//执行查询命令
ExecuteResult execute_select(Statement* statement, Table* table)
{
    Row row;
    Cursor* cursor = table_start(table);
    while (!cursor->end_of_table)
    {
        deserialize_row(cursor_value(cursor), &row);
        print_row(&row);
        cursor_advance(cursor);
    }
    
    free(cursor);

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement* statement, Table* table)
{
    switch(statement->type)
    {
        case STATEMENT_INSERT:
            return execute_insert(statement, table);
        case STATEMENT_SELECT:
            return execute_select(statement, table);
    }

    return EXECUTE_FAIL;
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("must supply a database filename.");
        exit(EXIT_FAILURE);
    }

    InputBuffer* inputbuffer = new_input_buffer();

    char* filename = argv[1];
    Table* table = db_open(filename);

    while(true)
    {
        print_prompt();
        read_input(inputbuffer);
        printf("input is %s\n", inputbuffer->buffer);

        if(inputbuffer->buffer[0] == '.')
        {
            switch(do_meta_command(inputbuffer, table))
            {
                case META_COMMAND_SUCCESS:
                    continue;
                case META_COMMAND_UNRECOGNIZED:
                    printf("unrecognized command %s\n", inputbuffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch(prepare_statement(inputbuffer, &statement))
        {
            case PREPARE_SUCCESS:
                break;
            case PREPARE_SYNTAX_ERROR:
                printf("Syntax error. Could not parse statement.\n");
                continue;
            case PREPARE_STRING_TOO_LONG:
                printf("Input String Too Long\n");
                continue;
            case PREPARE_UNRECOGNIZED:
                printf("unrecognized keywork at start of '%s'.\n", inputbuffer->buffer);
                continue;
            case PREPARE_NEGATIVE_ID:
                printf("Input Negative ID\n");
                continue;
        }

        switch(execute_statement(&statement, table))
        {
            case EXECUTE_SUCCESS:
                printf("executed.\n");
                break;
            case EXECUTE_TABLE_FULL:
                printf("Error: table full.\n");
                break;
            case EXECUTE_FAIL:
                printf("Error: execute fail.\n");
                break;
        }
    }
}


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef enum
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED
} MetaCommandResult;

typedef enum
{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED
} PrepareResult;

typedef enum
{
    STATEMENT_INSERT, STATEMENT_SELECT
} StatementType;

typedef void (*PFunc)(void* arg);

typedef struct 
{
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

typedef struct 
{
    char* cmd_name;
    PFunc cmd_func;
    int cmd_num;
} Command;

#define COLUME_USERNAME_SIZE 32
#define COLUME_EMAIL_SE
typedef struct 
{
    uint32_t id;
    char username[COLUME_USERNAME_SIZE];
    char email[COLUME_EMAIL_SIZE];
} Row;


typedef struct 
{
    StatementType type;
    Row row_to_insert;
} Statement;

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

void serialize_row(Row* source, void* destination)
{
    memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
    memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
    memcpy(destination + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

void deserialize_row(void* source, Row* destination)
{
    memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
    memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}

const uint32_t PAGE_SIZE = 4096;
#define TABLE_MAX_PAGES 100
const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

typedef struct 
{
    uint32_t num_rows;
    void* pages[TABLE_MAX_PAGES];
} Table;

void * row_slot(Table* table, uint32_t row_num)
{
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    void* page = table->pages[page_num];
    if(page == NULL)
    {
        page = malloc(PAGE_SIZE);
        table->pages[page_num] = page;
    }
    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;
    return page + byte_offset;
}

InputBuffer* new_input_buffer()
{
	InputBuffer* inputbuffer = (InputBuffer*) malloc(sizeof(InputBuffer));
	inputbuffer->buffer = NULL;
	inputbuffer->buffer_length = 0;
	inputbuffer->input_length = 0;

	return inputbuffer;
}

void print_prompt()
{
    printf("db > ");
}

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

void close_inputbuffer(InputBuffer* inputbuffer)
{
    free(inputbuffer->buffer);
    free(inputbuffer);
}

void db_exit(void* arg)
{
    InputBuffer* inputbuffer = (InputBuffer*) arg;
    close_inputbuffer(inputbuffer);
    printf("exit db\n");
    exit(EXIT_SUCCESS);
}

void db_show(void* arg)
{
    printf("call show func\n");
}

Command cmds[]=
{
    {
        ".exit", db_exit, 1
    },
    {
        ".show", db_show, 1
    },
    {
        NULL, NULL, 0
    }
};

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

MetaCommandResult do_meta_command(InputBuffer* inputbuffer)
{
    PFunc func = find_func(inputbuffer->buffer);
    if(func != NULL)
    {
        func(inputbuffer);
        return META_COMMAND_SUCCESS;
    }
    return META_COMMAND_UNRECOGNIZED;
}

PrepareResult prepare_statement(InputBuffer* inputbuffer, Statement* statement)
{
    if(strncmp(inputbuffer->buffer, "insert", 6) == 0)
    {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if(strncmp(inputbuffer->buffer, "select", 6) == 0)
    {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED;
}

void execute_statement(Statement* statement)
{
    switch(statement->type)
    {
        case STATEMENT_INSERT:
            printf("this is where we would do an insert.\n");
            break;
        case STATEMENT_SELECT:
            printf("this is where we would do an select.\n");
            break;
    }
}

int main()
{
    InputBuffer* inputbuffer = new_input_buffer();
    while(true)
    {
        print_prompt();
        read_input(inputbuffer);
        printf("input is %s\n", inputbuffer->buffer);

        if(inputbuffer->buffer[0] == '.')
        {
            switch(do_meta_command(inputbuffer))
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
            case PREPARE_UNRECOGNIZED:
                printf("unrecognized keywork at start of '%s'.\n", inputbuffer->buffer);
                continue;
        }

        execute_statement(&statement);
        printf("executed.\n");
    }
}


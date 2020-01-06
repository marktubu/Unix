#include <cstring>
#include <cstdio>

class MyString
{
private:
    char* m_data;
public:
    MyString(char* data = nullptr);
    MyString(const MyString& str);
    ~MyString();

    MyString& operator=(const MyString& str);

    void Print();
};

MyString::MyString(char* data)
{
    if(data == nullptr)
    {
        m_data = new char[1];
        m_data[0] = '\0';
    }
    else
    {
        int len = strlen(data);
        m_data = new char[len+1];
        strcpy(m_data, data);
    }
    
}

MyString::MyString(const MyString& str)
{
    int len = strlen(str.m_data);
    m_data = new char[len+1];
    strcpy(m_data, str.m_data);
}

MyString::~MyString()
{
    delete [] m_data;
    m_data = nullptr;
}

MyString& MyString::operator=(const MyString& str)
{
    if(this == &str)
        return *this;

    delete [] m_data;
    m_data = nullptr;
    
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
    return *this;
}

void MyString::Print()
{
    printf("m_data: %s", m_data);
}

void Test1()
{
    printf("Test1 begins:\n");

    char* text = "Hello world";

    MyString str1(text);
    MyString str2;
    str2 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str2.Print();
    printf(".\n");
}

// 赋值给自己
void Test2()
{
    printf("Test2 begins:\n");

    char* text = "Hello world";

    MyString str1(text);
    str1 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str1.Print();
    printf(".\n");
}

// 连续赋值
void Test3()
{
    printf("Test3 begins:\n");

    char* text = "Hello world";

    MyString str1(text);
    MyString str2, str3;
    str3 = str2 = str1;

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str2.Print();
    printf(".\n");

    printf("The expected result is: %s.\n", text);

    printf("The actual result is: ");
    str3.Print();
    printf(".\n");
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();

    return 0;
}
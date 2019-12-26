#include <iostream>
#include <vector>

using namespace std;

class String
{
public:
    String();
    String(const char* str);
    String(const String& str);
    ~String();
    String& operator=(const String& str);
    friend ostream& operator<<(ostream& os, const String& str);
private:
    char* m_data;
};

String::String()
{
    m_data = new char[1];
    m_data[0] = '\0';
}

String::String(const String& str)
{
    if(str.m_data == nullptr)
    {
        m_data = new char[1];
        m_data[0] = '\0';
        return;
    }

    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
}

String::String(const char* str)
{
    if(str == nullptr)
    {
        m_data = new char[1];
        m_data[0] = '\0';
        return;
    }

    m_data = new char[strlen(str) + 1];
    strcpy(m_data, str);
}

String::~String()
{
    delete [] m_data;
}

String& String::operator=(const String& str)
{
    if(m_data == str.m_data)
        return *this;
    
    delete [] m_data;
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
    return *this;
}

ostream& operator << (ostream& os, const String& str)
{
    os << str.m_data;
    return os;
}


void foo(String x)
{
}
void bar(const String& x)
{
}
String baz()
{
  String ret("world");
  return ret;
}
int main()
{
  String s0;
  String s1("hello");
  String s2(s0);
  String s3 = s1;
  s2 = s1;
  foo(s1);
  bar(s1);
  foo("temporary");
  bar("temporary");
  String s4 = baz();
  std::vector<String> svec;
  svec.push_back(s0);
  svec.push_back(s1);
  svec.push_back(baz());
  svec.push_back("good job");

  cout << s1 << s2 << endl;
}
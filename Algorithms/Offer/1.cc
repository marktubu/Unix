#include <iostream>
#include <string>

using namespace std;

class CMyString
{
public:
    CMyString(char* pData = nullptr);
    CMyString(const CMyString& str);
    ~CMyString(void);
    CMyString& operator=(const CMyString& str);
private:
    char* m_pData;
};

CMyString::CMyString(char* pData)
{
    if(pData == nullptr)
    {
        m_pData = new char[1];
        *m_pData = '\0';
        return;
    }

    m_pData = new char[strlen(pData)] + 1;
    strcpy(m_pData, pData);
}

CMyString::CMyString(const CMyString& str)
{
    m_pData = new char[strlen(str.m_pData) + 1];
    strcpy(m_pData, str.m_pData);
}

CMyString::~CMyString()
{
    if(m_pData != nullptr)
    {
        delete [] m_pData;
    }
}

CMyString& CMyString::operator=(const CMyString& str)
{
    if(&str == this)
        return *this;
    
    delete [] m_pData;
    m_pData = new char[strlen(str.m_pData) + 1];
    strcpy(m_pData, str.m_pData);
    return *this;
}
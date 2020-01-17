#include <cstdio>

long long StrToIntCore(const char* str, bool minus);

enum Status {kValid = 0, kInvalid};
int g_nStatus = kValid;

int StrToInt(const char* str)
{
    long long num = 0;
    g_nStatus = kInvalid;

    if(str != nullptr && *str != '\0')
    {
        bool minus = false;
        if(*str == '+')
            str++;
        else if(*str == '-')
        {
            minus = true;
            str++;
        }

        int flag = minus?-1:1;
        while(*str != '\0')
        {
            if(*str >= '0' && *str <= '9')
            {
                num = num * 10 + flag * (*str - '0');
                if(!minus && num > 0x7fffffff ||
                    minus && num < (signed int)0x80000000)
                {
                    num = 0;
                    break;
                }
            }
            else
            {
                num = 0;
                break;
            }
            
            str++;
        }

        if(*str == '\0')
            g_nStatus = kValid;
    }
    return (int) num;
}

long long StrToIntCore(const char* digit, bool minus)
{
    return 0;
}

// ====================测试代码====================
void Test(const char* string)
{
    int result = StrToInt(string);
    if(result == 0 && g_nStatus == kInvalid)
        printf("the input %s is invalid.\n", string);
    else
        printf("number for %s is: %d.\n", string, result);
}

int main(int argc, char* argv[])
{
    Test(nullptr);

    Test("");

    Test("123");

    Test("+123");
    
    Test("-123");

    Test("1a33");

    Test("+0");

    Test("-0");

    //有效的最大正整数, 0x7FFFFFFF
    Test("+2147483647");    

    Test("-2147483647");

    Test("+2147483648");

    //有效的最小负整数, 0x80000000
    Test("-2147483648");    

    Test("+2147483649");

    Test("-2147483649");

    Test("+");

    Test("-");

    return 0;
}
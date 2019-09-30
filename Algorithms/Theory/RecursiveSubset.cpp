#include <iostream>

using namespace std;

void RecursiveSubset(string result, string remain)
{
    if(remain.size() == 0)
    {
        cout << "substring is : " << result << endl;
        return;
    }

    string rem = remain.substr(0, 1);
    remain = remain.substr(1);
    RecursiveSubset(result, remain);
    RecursiveSubset(result + rem, remain);
}

//字符串的所有排列
void RecursiveOrder(string result, string remain)
{
    if(remain.size() == 0)
    {
        cout << "result string : " << result << endl;
        return;
    }
    
    for (size_t i = 0; i < remain.size(); i++)
    {
        //同一个循环中需要重复使用原始的remain数据，因此在单次循环中不可改变remain自身
        string ret = result + remain[i];
        string rem = remain.substr(0, i) + remain.substr(i+1, remain.size() - i - 1);
        RecursiveSubset(ret, rem);
    }
    
}

int main()
{
    string result;
    string remain = "abcdef";
    RecursiveSubset(result, remain);
    return 0;
}
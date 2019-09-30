#include <iostream>

using namespace std;

void RecursiveSubset(string result, string remain)
{
    if(remain.size() == 0)
    {
        cout << "result string : " << result << endl;
        return;
    }
    
    for (size_t i = 0; i < remain.size(); i++)
    {
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
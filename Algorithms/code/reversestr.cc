#include <iostream>
#include <string>
using namespace std;

void reverse(string& str, int start, int end)
{
    if(str.empty())
        return;
    
    while(start < end)
    {
        char tmp = str[start];
        str[start] = str[end];
        str[end] = tmp;

        ++start;
        --end;
    }
}

void reverseStr(string& str)
{
    if(str.empty())
        return;
    
    int len = str.size();
    int start = 0;
    int end = len-1;
    reverse(str, start, end);

    start = 0;
    end = 0;
    while(start < len)
    {
        while(str[start] == ' ')
            ++start;

        end = start;
        while(end < len-1 && str[end+1] != ' ')
            ++end;

        reverse(str, start, end);
        start = end + 2;
    }
}


int main()
{
    string str = "  this is    a    word   ";
    reverseStr(str);
    cout << str << endl;
    return 0;
}
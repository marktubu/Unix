#include <iostream>
#include <string.h>
#include <cstdint>

using namespace std;

int getmaxlength(const string& s, int start, int end)
{
    int max_length = 0;
    while (--start >= 0 && ++end < s.length())
    {
        if(s[start] == s[end])
        {
            max_length += 2;
        }
        else
        {
            break;
        }
    }

    return max_length;
}

int getpalindromelength(const string& s, int pos)
{
    if(s.empty() || pos >= s.length())
    {
        return 0;
    }

    int max_length = 1;
    if((pos-1)>=0 && (pos+1)<s.length() && s[pos-1] == s[pos+1])
    {
        int max_length1 = 1;
        int start = pos;
        int end = pos;

        max_length1 += getmaxlength(s, start, end);

        if(max_length1 > 1)
        {
            max_length = max_length1;
        }
    }

    if((pos-1)>=0 && s[pos] == s[pos-1])
    {
        int max_length2 = 0;
        int start = pos;
        int end = pos-1;

        max_length2 += getmaxlength(s, start, end);

        if(max_length2 > max_length)
        {
            max_length = max_length2;
        }
    }

    return max_length;
}

string longestPalindrome(string s) 
{
    if(s.length() < 2)
    {
        return s;
    }

    int max_length = 0;
    char result[1001];
    int target_pos = 0;
    for (int i = 0; i < s.length(); i++)
    {
        int len = getpalindromelength(s, i);
        if(len > max_length)
        {
            max_length = len;
            target_pos = i;
        }
    }

    memset(result, 0, sizeof(char) * 1001);
    int start = target_pos - max_length / 2;
    s.copy(result, max_length, start);
    result[max_length] = '\0';

    return std::string(result);
}

int main()
{
    string ss("aa");
    std::string ret = longestPalindrome(ss);
    cout << "longestPalindrome : " << ret << " ret length: " << ret.length() << endl;
    return 0;
}
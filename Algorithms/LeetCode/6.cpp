#include <iostream>
#include <string.h>
#include <cstdint>
#include <vector>

using namespace std;

string convert(string s, int numRows) 
{
    size_t len = s.length();
    if(numRows >= len || numRows == 1)
        return s;

    vector<string> str_vec(numRows);

    bool goingDown = false;
    size_t row = 0;

    for (char ch : s)
    {
        str_vec[row].push_back(ch);
        if(row == 0 || row == numRows - 1)
            goingDown = ! goingDown;

        row += goingDown ? 1 : -1; 
    }
    
    string ret;
    for (string str : str_vec)
    {
        ret += str;
    }
    
    return ret;
}

string convert2(string str, int numRows) 
{
    size_t len = str.length();
    if(len <= numRows || numRows <= 1)
        return str;
    
    vector<string> strs = vector<string>(numRows, string());

    int current = 0;
    int step = 1;
    for (auto s : str)
    {
        strs[current].push_back(s);
        current += step;
        if(current <= 0 || current >= numRows-1)
        {
            step = -step;
        }
    }
    
    string ret;
    for (size_t i = 0; i < strs.size(); i++)
    {
        ret = ret + strs[i];
    }

    return ret;
}

int main()
{
    string s = "LEETCODEISHIRING";
    string ret = convert(s, 3);
    cout << "ret string is : " << ret <<endl;
    return 0;
}
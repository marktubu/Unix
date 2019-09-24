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

int main()
{
    string s = "LEETCODEISHIRING";
    string ret = convert(s, 3);
    cout << "ret string is : " << ret <<endl;
    return 0;
}
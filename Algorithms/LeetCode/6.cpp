#include <iostream>
#include <string.h>
<<<<<<< HEAD
=======
#include <cstdint>
#include <vector>
>>>>>>> 397566d7bd5e599002a5005d3d3d34afd4272333

using namespace std;

string convert(string s, int numRows) 
{
<<<<<<< HEAD
    
=======
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
>>>>>>> 397566d7bd5e599002a5005d3d3d34afd4272333
}

int main()
{
<<<<<<< HEAD
    
=======
    string s = "LEETCODEISHIRING";
    string ret = convert(s, 3);
    cout << "ret string is : " << ret <<endl;
>>>>>>> 397566d7bd5e599002a5005d3d3d34afd4272333
    return 0;
}
#include <iostream>
#include <string.h>
#include <cstdint>
#include <vector>
#include <limits.h>
#include <sstream> 
#include <string>
#include <stdlib.h>
#include <algorithm>    // std::min

using namespace std;

string intToRoman(int num) 
{
    vector<char> table = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    string str_num = to_string(num);
    int len = str_num.size();
    int base = 2 * len - 2;
    int max_num = std::pow(10, len-1);

    string ret;
    
    int left_num = (int) num / max_num;
    if(left_num >= 5)
    {
        
    }
    
    if(num >= 1000)
    {
        ret += "M";
        ret += intToRoman(num % 1000);
    }
    else if(num >= 100)
    {
        
        ret += intToRoman(num % 100);
    }
    
}

int main(int argc, char* argv[])
{

}
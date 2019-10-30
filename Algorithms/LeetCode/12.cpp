
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <cmath>
#include <time.h>

using namespace std;

vector<int> nums = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
vector<string> table2 = {"M", "CM", "D", "CD","C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

//贪心算法
string intToRoman(int num)
{
    int index = 0;
    string ret;
    while (num > 0 && index < nums.size())
    {
        while (num >= nums[index])
        {
            num -= nums[index];
            ret += table2[index];
        }
        
        index++;
    }
    return ret;
}

string intToRoman2(int num) 
{
    if(num == 0)
        return "";
    vector<string> table = {"I", "V", "X", "L", "C", "D", "M"};
    int len = 0;
    if(num > 999)
    {
        len = 4;
    }
    else if(num > 99)
    {
        len = 3;
    }
    else if(num > 9)
    {
        len = 2;
    }
    else
    {
        len = 1;
    }
    
    int base = 2 * len - 2;
    int factor = len - 1;
    //pow(10,2) = 99.999... 转换为int 为99，因此需要round
    int min_num = std::round(pow(10, factor));

    string ret;
    
    int left_num = (int) num / min_num;
    //cout << base << endl;
    if(left_num == 9)
    {
        ret = table[base] + table[base + 2];
    }
    else if(left_num >= 5)
    {
        ret += table[base+1];
        for(int i=0;i<left_num - 5;i++)
        {
            ret += table[base];
        }
    }
    else if(left_num == 4)
    {
        ret = table[base] + table[base + 1];
    }
    else
    {
        for (size_t i = 0; i < left_num; i++)
        {
            ret += table[base];
        }
    }
    
    int _n = num % min_num;
    return ret += intToRoman(_n);
}

int main(int argc, char* argv[])
{
    clock_t start,end;
    start = clock();
    string ret = intToRoman(1994);
   
    end = clock();
    cout<<"time : " <<  (double)(end-start) << endl;
    cout << "ret: "<<ret<<endl;
    return 0;
}
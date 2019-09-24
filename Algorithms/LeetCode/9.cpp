#include <iostream>
#include <string.h>
#include <cstdint>
#include <vector>
#include <limits.h>
#include <sstream> 
#include <string>
#include <cstdlib>

using namespace std;

//有符号整数反转
bool reverse(int x) 
{
    if(x < 0)
        return false;

    vector<int> vec;
    int tmp = x;
    while (tmp > 0)
    {
        int a = tmp % 10;
        tmp = tmp / 10;
        
        vec.push_back(a);
    }

    int start = 0;
    int end = vec.size()-1;

    while (start <= end)
    {
        if(vec[start++] != vec[end--])
        {
            return false;
        }
    }

    return true;
}

int main(int argc, char* argv[])
{
    if(argc < 1)
        return 0;
    
    char* arg = argv[1];
    cout << "arg " << arg << "  " << argv[0] << endl;
    int number; 
    std::stringstream ss;

    string text(arg);
    ss << text;//可以是其他数据类型
    ss >> number; //string -> int

    bool ret = reverse(number);
    cout << "reverse : " << ret << endl;
    return 0;
}
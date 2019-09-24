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
int reverse(int x) 
{
    if(x == INT_MIN)
        return 0;
    int sign = x < 0 ? -1 : 1;

    uint32_t abs_x = abs(x);

    int max_div_10 = (int)INT_MAX / 10;
    int max_mod_10 = INT_MAX % 10;

    int ret = 0;
    while (abs_x > 0)
    {
        int a = abs_x % 10;
        abs_x = (uint32_t)abs_x / 10;

        if(ret > max_div_10 || (ret == max_div_10 && a > max_mod_10))
            return 0;
        ret = ret * 10 + a;
    }
    
    return ret * sign;
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

    int ret = reverse(number);
    cout << "reverse : " << ret << endl;
    return 0;
}
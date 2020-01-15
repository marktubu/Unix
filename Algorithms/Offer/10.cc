#include <iostream>

using namespace std;

long long Fabonacci(unsigned int n)
{
    int result[2] = {0, 1};
    if(n < 2)
        return result[n];
    
    long long NMinusOne = 1;
    long long NMinusTwo = 0;

    long long ret = 0;
    for (size_t i = 2; i < n; i++)
    {
        ret = NMinusOne + NMinusTwo;
        NMinusTwo = NMinusOne;
        NMinusOne = ret;
    }
    
    return ret;
}
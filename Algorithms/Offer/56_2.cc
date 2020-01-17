#include <iostream>
#include <exception>

using namespace std;

int FindNumberAppearingOnce(int numbers[], int length)
{
    if(numbers == nullptr || length <= 0)
        return -1;
    
    int bitnum[32] = {0};
    for (size_t i = 0; i < length; i++)
    {
        int bitmask = 1;
        for (size_t j = 31; j >=0; j--)        {
            bitnum[j] += numbers[i] & bitmask;
            bitmask = bitmask << 1;
        }
        
    }

    int result = 0;
    for (size_t i = 0; i < 32; i++)
    {
        int num = bitnum[i] % 3;
        result = result << 1;
        result += num;
    }
    
    return result;   
}
#include <iostream>

using namespace std;

int FindGreatestSumInSubArray(int* pData, int length)
{
    if(pData == nullptr || length <= 0)
        return 0;
    
    int greatest = 0x80000000;
    int sum = 0;
    for (size_t i = 0; i < length; i++)
    {
        if(sum <= 0)
        {
            sum = pData[i];
        }
        else
        {
            sum += pData[i];
        }
        
        if(sum > greatest)
        {
            greatest = sum;
        }
    }
    
    return greatest;
}
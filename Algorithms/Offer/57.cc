#include <iostream>

using namespace std;

bool FindNumbersWithSum(int numbers[], int length, int sum, int* num1, int* num2)
{
    if(numbers == nullptr || length <= 0 || num1 == nullptr || num2 == nullptr)
        return false;
    
    int front = 0;  
    int back = length - 1;

    while(front < back)
    {
        long long tmp = numbers[front] + numbers[back];
        if(tmp == sum)
        {
            *num1 = numbers[front];
            *num2 = numbers[back];
            return true;
        }
        else if(tmp > sum)
        {
            back--;
        }
        else
        {
            front++;
        }
    }

    return false;
}
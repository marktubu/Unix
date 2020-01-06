#include <iostream>

int main()
{
    int arr[7] = {2,3,0,1,2,5,3};

    for (size_t i = 0; i < 7; )
    {
        if(arr[i] == i)
        {
            ++i;
        }    
        else
        {
            if(arr[i] < 7)
            {
                if(arr[arr[i]] == arr[i])
                {
                    std::cout << "find : " << arr[i] << std::endl;
                    break;
                }
                else
                {
                    int tmp = arr[arr[i]];
                    arr[arr[i]] = arr[i];
                    arr[i] = tmp;
                }
            }
        }
        
    }
    
}
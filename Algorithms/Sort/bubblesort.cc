#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

void swap(int *xp, int *yp)  
{  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
} 

//升序，递增
void bubbleSort(int arr[], int n)  
{  
    int i, j;  
    for (i = 0; i < n-1; i++)      
    {
        for (j = 0; j < n-i-1; j++)  
        {
            if (arr[j] > arr[j+1])  
                swap(&arr[j], &arr[j+1]); 
        }     
    }
}

void bubbleSort(vector<int>& arr)  
{  
    int i, j;  
    int n = arr.size();
    for (i = 0; i < n-1; i++)      
    {
        for (j = 0; j < n-i-1; j++)  
        {
            if (arr[j] > arr[j+1])  
                swap(&arr[j], &arr[j+1]); 
        }     
    }
}

int main()
{
    int arr[10] = {22, 1,34, 5, 11, 12, 13, 5, 8, 10};
    bubbleSort(arr, 10);

    for (size_t i = 0; i < 10; i++)
    {
        cout << "arr " << i << "  " << arr[i];
    }
    
}
#include <iostream>
#include <vector>

using namespace std;

void swap(std::vector<int>& arr, int lidx, int ridx)
{
    int tmp = arr[lidx];
    arr[lidx] = arr[ridx];
    arr[ridx] = tmp;
}

int partition(std::vector<int>& arr, int low, int high)
{
    int pivot = arr[low];
    int left = low;
    int right = high;
    while(left < right)
    {
        while (arr[left] <= pivot)
        {
            ++left;
        }
        while (arr[right] > pivot)
        {
            --right;
        }
        
        if(left < right)
        {
            swap(arr, left, right);
        }
    }
    swap(arr, low, right);
    return right;
}

void quicksort(std::vector<int>& arr, int left, int right)
{
    if(left < right)
    {
        int index = partition(arr, left, right);
        quicksort(arr, left, index-1);
        quicksort(arr, index+1, right);
    }
}

int main()
{
    vector<int> data;
    int i=0;
    int value=0;
    vector<int>::iterator itr;
    while(i < 10)
    {
        value = rand() % 100;
        data.push_back(value);
        i++;
    }
    cout << "Before Sorting: ";
    for(itr=data.begin();itr !=data.end(); itr++)
    {
        cout <<  *itr << " " ;
    }
    quicksort(data,0,9);
    cout << "\nAfter sorting: ";
    
    for(itr=data.begin();itr !=data.end(); itr++)
    {
        cout <<  *itr << " " ;
    }
    return 0;
}
#include <iostream>

using namespace std;

void sort(int arr[], int left, int right)
{

}

void merge(int arr[], int left, int mid, int right)
{
    int tmp[right - left + 1];
    
}

void mergesort(int arr[], int left, int right)
{
    if(left == right)
        return;
    int mid = left + (right - left) / 2;
    mergesort(arr, left, mid);
    mergesort(arr, mid, right);
    merge(arr, left, mid, right);
}

int main()
{

}
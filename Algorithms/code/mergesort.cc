#include <iostream>

using namespace std;

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1];
    int R[n2];

    for (size_t i = 0; i < n1; i++)
    {
        L[i] = arr[l+i];
    }

    for (size_t i = 0; i < n2; i++)
    {
        R[i] = arr[m+i+1];
    }
    
    int i=0;
    int j=0;
    int k=l;
    while (i<n1 && j<n2)
    {
        if(L[i] > R[j])
        {
            arr[k] = R[j];
            j++;
        }
        else
        {
            arr[k] = L[i];
            i++;
        }
        k++;
    }
    
    while (i<n1)
    {
        arr[k++] = L[i++];
    }
    while (j<n2)
    {
        arr[k++] = R[j++];
    }
}

void mergesort(int arr[], int l, int r)
{
    if(arr == nullptr)
        return;
    if(l < r)
    {
        int m = l + (r-l)/2;
        mergesort(arr, l, m);
        mergesort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void printarr(int arr[], int length)
{
    for (size_t i = 0; i < length; i++)
    {
        cout << "arr i " << i << "  " << arr[i] << endl;  
    }
    
}

int main()
{
    int arr[] = {2,66,34,32,3,4,5,2,77,43,22};
    mergesort(arr, 0, 10);
    printarr(arr, 11);
    return 0;
}
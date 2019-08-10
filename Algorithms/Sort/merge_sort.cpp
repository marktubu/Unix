#include <iostream>
#include <limits.h>

using namespace std;

template<unsigned N>
void merge(int (&arr)[N], int p, int q, int r)
{
    //p -- q
    int * arr_l = new int[q-p+2];
    //q+1 -- r
    int * arr_r = new int[r-q+1];

    for(int i=0;i<q-p+1;++i)
    {
        int j = i+p;
        arr_l[i] = arr[j];
    }

    for(int i=0;i<r-q;++i)
    {
        int j = i+q+1;
        arr_r[i] = arr[j];
    }

    arr_l[q-p+1] = INT_MAX;
    arr_r[r-q] = INT_MAX;

    int l_index = 0;
    int r_index = 0;
    for(int k = p;k<r+1;++k)
    {
        if(arr_l[l_index] <= arr_r[r_index])
        {
            arr[k] = arr_l[l_index];
            l_index ++;
        }
        else
        {
            arr[k] = arr_r[r_index];
            r_index ++;
        }
    }

    delete [] arr_l;
    delete [] arr_r;
}

template<unsigned N>
void merge_sort(int (&arr)[N], int p, int r)
{
    if(p < r)
    {
        int q = (int)(p+r)/2;
        merge_sort(arr, p, q);
        merge_sort(arr, q+1,r);
        merge(arr, p, q, r);
    }
}

template<typename T, unsigned N>
void print(T (&arr)[N])
{
    for(int i=0;i<N;i++)
    {
        cout<<"template T array number " << i << "  " << arr[i]<<endl;
    }
}

int main()
{
    //int array
    int array[] = {31, 41, 59,26, 2, 21, 13, 41, 58};
 
    //insertion sort
    merge_sort(array, 0 , 8);

    //test sort result
    print(array); 
}
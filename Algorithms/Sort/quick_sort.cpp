#include <iostream>

using namespace std;

template<unsigned N>
int partition(int (&arr) [N], int p, int r)
{
    int x = arr[r];
    int i = p-1;

    for(int j=p;j<r;++j)
    {
        if(arr[j] < x)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i+1];
    arr[i+1] = arr[r];
    arr[r] = temp;

    return i+1;
}

template<unsigned N>
void quick_sort(int (&arr) [N], int p, int r)
{
    if(p < r)
    {
        int q = partition(arr, p, r);
        quick_sort(arr, p, q);
        quick_sort(arr, q+1, r);
    }
}

int main()
{
    int array[] = {31, 41, 59,26, 41, 58, 2, 4, 7, 1};
    quick_sort(array, 0, 9);

    for(int i=0;i<10;++i)
    {
        cout << "array : " << array[i] << endl;
    }
}
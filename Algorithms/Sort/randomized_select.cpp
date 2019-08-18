#include <iostream>

using namespace std;

//使用快速排序的思路解决选择问题

template<unsigned N>
int randomized_partition(int (&arr)[N], int p, int r)
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
int randomized_select(int (&arr)[N], int p, int r, int i)
{
    if(p < r)
    {
        int q = randomized_partition(arr, p, r);
        int k = q-p;
        if(k==i)
        {
            return arr[q]; 
        }
        else if(k > i)
        {
            return randomized_select(arr, p, q, i);
        }
        else
        {
            return randomized_select(arr, q, r, i-k);
        }
        
    }

    return arr[p];
}

int main()
{
    int array[] = {31, 41, 59,26, 41, 58, 2, 4, 7, 1};
    int result = randomized_select(array, 0, 9, 4);
    cout<<"the 4th smallest number is : " << result<< endl;
    return 0;
}
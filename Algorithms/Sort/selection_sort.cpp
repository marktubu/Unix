#include <iostream>

using namespace std;

//1.初始化：第一次循环之前无排序好元素
//2.保持：内层for循环每次找出i之后的所有元素中最小的值，
//并与i交换，可保证每次i处的值都是剩下元素中最小的。
//3.终止：导致for循环终止的条件是i>=size-1.
//因为每次循环迭代i增加1，必有i=size-1.
//此时从i=0到i=size-2都已经排好序，
//size-1处（即最后一位）自然是最大值，
//可推断出整个数组已经排好序。
template<unsigned N>
void selection_sort(int (&arr)[N])
{
    int size = N;
    for(int i=0;i<size-1;++i)
    {
        int key = arr[i];
        int findindex = -1;
        for(int j=i+1;j<size;++j)
        {
            if(arr[j] < key)
            {
                key = arr[j];
                findindex = j;
            }
        }

        if(findindex != -1)
        {
            int temp = arr[i];
            arr[i] = arr[findindex];
            arr[findindex] = temp;
        }
    }
}

/*
行数        运行时间        运行次数
17          c1              n
19          c2             n-1
20          c3             n-1
21          c4             i=0->n-2 求和 t(i)
23          c5             i=0->n-2 求和 t(i-1)
25          c6             i=0->n-2 求和 t(i-1)
26          c7             i=0->n-2 求和 t(i-1)
30          c8             n-1
32          c9             n-1
33          c10            n-1
34          c11            n-1

最坏情况：数组逆序

 */

template<unsigned N>
void print(int (&arr)[N])
{
    for(int i=0;i<N;i++)
    {
        cout<<"array number " << i << "  " << arr[i]<<endl;
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
    int array[] = {31, 41, 59,26, 41, 58};

    //insertion sort
    selection_sort(array);

    //test sort result
    print(array); 
}
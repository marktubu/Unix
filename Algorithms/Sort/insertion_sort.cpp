#include <iostream>

using namespace std;

template<unsigned N>
void insertion_sort(int (&arr)[N])
{
    int size = N;
    for(int i=1;i<size;i++)
    {
        int key = arr[i];

        //此处如果j的类型使用unsigned,那么当j=0时执行j--,
        //j会变成一个很大的值4294967295,即0xffffffff
        //从而引发段错误Segmentation fault
        //因此将size, i, j的类型改为int
        int j = i-1;
        while(j>=0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j--;
        }

        arr[j+1] = key;
    }
}

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
    
    //float array
    float array2[] = {31.23, 41.23, 59.23,26.23, 41.23, 58.23};
    
    //insertion sort
    insertion_sort(array);

    //test sort result
    print(array); 

    //test template print function
    print(array2);
}
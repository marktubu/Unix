#include <iostream>

using namespace std;

/*
原始定义为如下定义，在数组第一个值的下标为1的编程语言中是成立的，
但 C/C++ 中数组第一个值的下标为0，因此需进行+1
#define LEFT(i) (i << 1)
#define RIGHT(i) ((i << 1) + 1)
*/

#define LEFT(i) ((i << 1) + 1)
#define RIGHT(i) ((i << 1) + 2)
#define PARENT(i) ((i-1) >> 1)

template<unsigned N>
void max_heapify(int (&arr) [N], int i, int heap_size)
{
    int l = LEFT(i);
    int r = RIGHT(i);

    int largest = i;
    if(l < heap_size && arr[l] > arr[largest])
    {
        largest = l;
    }

    if(r < heap_size && arr[r] > arr[largest])
    {
        largest = r;
    }

    if(largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        max_heapify(arr, largest, heap_size);
    }
}

template<unsigned N>
void build_max_heap(int (&arr) [N], int heap_size)
{
    int size = N/2-1;
    for(int i=size;i>=0;i--)
    {
        max_heapify(arr, i, heap_size);
    }
}

template<unsigned N>
void heap_sort(int (&arr)[N], int heap_size)
{
    if(heap_size <= 1)
    {
        return;
    }

    build_max_heap(arr, heap_size);

    int temp = arr[0];
    arr[0] = arr[heap_size-1];
    arr[heap_size-1] = temp;

    heap_size--;

    heap_sort(arr, heap_size);
}

int main()
{
    int array[] = {31, 41, 59,26, 41, 58, 2, 4, 7, 1, 23, 123};
    heap_sort(array, 12);

    for(int i=0;i<12;++i)
    {
        cout << "array : " << array[i] << endl;
    }
}

#include <iostream>
#include <climits>

using namespace std;

/*
原始定义为如下定义，在数组第一个值的下标为1的编程语言中是成立的，
但 C/C++ 中数组第一个值的下标为0，因此需进行+1
#define LEFT(i) (i << 1)
#define RIGHT(i) ((i << 1) + 1)
*/

#define LEFT(i) ((i << 1) + 1)
#define RIGHT(i) ((i << 1) + 2)
#define PARENT(i) (i == 0 ? -1 : (i-1) >> 1)



//建立最大堆的操作
template<unsigned N>
void max_heapify_max_heap(int (&arr) [N], int i, int heap_size)
{
    int l = LEFT(i);
    int r = RIGHT(i);

    int min = i;
    if(l < heap_size && arr[l] < arr[min])
    {
        min = l;
    }

    if(r < heap_size && arr[r] < arr[min])
    {
        min = r;
    }

    if(min != i)
    {
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;

        max_heapify_max_heap(arr, min, heap_size);
    }
}

//建立最小堆的操作
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
        max_heapify_max_heap(arr, i, heap_size);
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
    cout << "max " << arr[0] << endl;
    int temp = arr[0];
    arr[0] = arr[heap_size-1];
    arr[heap_size-1] = temp;

    heap_size--;

    heap_sort(arr, heap_size);
}

template<unsigned N>
void increase_key(int (&arr)[N], int x, int k)
{
    if(arr[x] < k)
    {
        arr[x] = k;
        while(PARENT(x) >=0 && arr[PARENT(x)] < k)
        {
            int value = arr[x];
            arr[x] = arr[PARENT(x)];
            arr[PARENT(x)] = value;

            x = PARENT(x);
        }
    }
}

template<unsigned N>
void insert(int (&arr)[N], int key, int heap_size)
{
    heap_size ++;
    arr[heap_size] = INT_MIN;

    increase_key(arr, heap_size, key);    
}

template<unsigned N>
int maximum(int (&arr)[N])
{
    return arr[0];
}

template<unsigned N>
int extract_max(int (&arr)[N], int heap_size)
{
    int max = arr[0];
    arr[0] = arr[heap_size-1];
    arr[heap_size-1] = 0;
    heap_size--;
    max_heapify(arr, 0, heap_size);
    return max;
}

int main()
{
    int array[] = {31, 41, 59,26, 41, 58, 2, 4, 0, 0};
    heap_sort(array, 8);
    for(int i=0;i<10;++i)
    {
        cout << "array sort : " << array[i] << endl;
    }
    int max = extract_max(array, 8);
    cout << "max 222" << max <<endl;
    for(int i=0;i<10;++i)
    {
        cout << "array : " << array[i] << endl;
    }

    insert(array, 100, 7);
    for(int i=0;i<10;++i)
    {
        cout << "array after insert : " << array[i] << endl;
    }
}

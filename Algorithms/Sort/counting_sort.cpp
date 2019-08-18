#include <iostream>

using namespace std;

//当k值特别大怎么办
template<unsigned N>
void counting_sort(int (&arr) [N], int (&target_arr) [N], int k)
{
    int *count_arr = new int[k];
    for (size_t i = 0; i < k; i++)
    {
        count_arr[i] = 0;
    }
    
    for (size_t i = 0; i < N; i++)
    {
        count_arr[arr[i]] ++;
    }
    
    for (size_t i = 1; i < k; i++)
    {
        count_arr[i] += count_arr[i-1];
    }
    
    for (size_t i = 0; i < N; i++)
    {
        target_arr[count_arr[arr[i]]] = arr[i];
        count_arr[arr[i]] --;
    }
    

    delete [] count_arr;
}


int main()
{
    int array[] = {31, 41, 59,26, 41, 58, 2, 4, 7, 1};
    int target_arr[10];
    counting_sort(array, target_arr, 60);

    for(int i=0;i<10;++i)
    {
        cout << "array : " << target_arr[i] << endl;
    }
}
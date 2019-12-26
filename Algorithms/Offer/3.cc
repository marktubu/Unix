#include <iostream>
#include <array>

using namespace std;

void swap(int& a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    array<int, 7> arr = {2, 3, 1, 0, 2, 5, 3};
    for(int i=0;i<arr.size();++i)
    {
        auto num = arr[i];
        if(num == i)
            continue;
        if(num == arr[num])
        {
            cout << "num is : " << num << endl;
            //break;
        }
        else
        {
            swap(arr[i], arr[num]);
        }
        
    }
    return 0;
}
#include <iostream>

using namespace std;

#define IMPOSSIBLE_VALUE -1

template <typename T>
T& find(T src[],const int& len)
{
    for(int i=0;i<len;)
    {
        if( IMPOSSIBLE_VALUE == src[i] )
        {
            break;
        }
        i = src[i];
        src[i] = IMPOSSIBLE_VALUE;
    }
    return src[i];
}

int main()
{
    int src[1001];
    for (size_t i = 0; i < 1000; i++)
    {
        src[i] = i;
    }

    src[1000] = 200;
    
    int ret = find(src, 1001);
    cout << "find duplicated number: " << ret << endl;
}
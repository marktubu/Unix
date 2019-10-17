#include <iostream>

using namespace std;

enum {_ALIGN = 8};

size_t freelist_index(size_t __bytes) {
        return (((__bytes) + (size_t)_ALIGN-1)/(size_t)_ALIGN - 1);
}

void testFunc(int, void*)
{
    cout <<"test ya yuan "<<endl;
}

int main()
{
    size_t s = freelist_index(0);
    cout << "free list index : " << s << endl;

    testFunc(0, 0);
    return 0;
}
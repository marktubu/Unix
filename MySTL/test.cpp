#include <iostream>
#include <sstream> 
#include <string>

using namespace std;

enum {_ALIGN = 8};

size_t freelist_index(size_t __bytes) {
        return (((__bytes) + (size_t)_ALIGN-1)/(size_t)_ALIGN - 1);
}

size_t fib(size_t n)
{
    size_t a{0};
    size_t b{1};

    for(size_t i{0}; i<n;++i)
    {
        const size_t old_b{b};
        b+=a;
        a = old_b;
    }

    return b;
}

void testFunc(int, void*)
{
    cout <<"test ya yuan "<<endl;
}

int& return_int_ref() {
    int a {123};
    return a; // Returning a reference to something on the stack!
}

int main(int argc, char* argv[])
{
    for(int i=0;i<argc;++i)
    {
        cout << "arg " << i << " is: " << argv[i] << endl;
    }

    char* count = argv[1];

    int number = std::atoi(count);

    size_t ret = fib(number);
    cout << "fib : " << ret << endl;

    int &int_ref {return_int_ref()};

    //std::cout << "Some stack overwriting intermediate print\n";

    std::cout << int_ref << '\n';

    return 0;
}
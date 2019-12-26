#include <iostream>

using namespace std;

int main()
{
    const char * a = "123";
    const char * b = "123";
    bool is = a == b;
    cout <<  a << " b : " << b << endl;
    return 0;
}
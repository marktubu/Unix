#include <stdio.h>
#include <string>
#include <utility>
#include <iostream>

using namespace std;
 
class Foo
{
public:
    Foo(){ cout << "constructor" << endl;}
	Foo(int _x) : x(_x){ cout << "constructor 2" << endl;}
    Foo(const Foo& v){ cout << "copy constructor" << endl;}
    ~Foo(){ cout << "deconstructor " << x << endl;}
    
	Foo operator=(Foo& vec);
	Foo& operator=(const Foo& foo);

    int x;
};

Foo Foo::operator=(Foo& foo)
{
	cout << "operator = 1" << endl;
	Foo f;
	f.x = foo.x;
	return f;
}

Foo& Foo::operator=(const Foo& foo)
{
	cout << "operator = 2" << endl;
	this->x = foo.x;
	return *this;
}

int main(int argc, char* argv[])
{
	Foo v(1);
	Foo v2 = v;
	v2.x = 2;
	return 0;
}
#include <iostream>
#include <thread>

void do_something(int& k)
{
	k = k * (k+1);
}

struct func
{
	int& i;
	func(int& _i):i(_i){}
	
	void operator()()
	{
		for(unsigned j=0;j<3000000;++j)
		{
			do_something(i);
		}
	}
};

void f()
{
	int state = 0;
	func myfunc(state);
	std::thread test(myfunc);

	try
	{
		do_something(state);
	}
	catch(...)
	{
		test.join();
		throw;
	}
	test.join();
}

int main()
{
	f();
}

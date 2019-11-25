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

void oops()
{
	int state = 0;
	func myfunc(state);
	std::thread test_func(myfunc);
	test_func.detach();
	std::cout << "state : " << state << std::endl;
}

int main()
{
	oops();
}

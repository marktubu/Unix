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
		for(unsigned j=0;j<1000000;++j)
		{
			do_something(i);
		}
	}
};

class thread_guard
{
private:
	std::thread& t;

public:
	thread_guard(std::thread& _t):t(_t){}
	thread_guard(const thread_guard&) = delete;
	~thread_guard()
	{
		if(t.joinable())
		{
			t.join();
		}
	}

	thread_guard& operator =(const thread_guard&) = delete;
};

void f()
{
	int state = 0;
	func myfunc(state);
	std::thread test(myfunc);
	thread_guard t_guard(test);

	try
	{
		do_something(state);
	}
	catch(...)
	{
		throw;
	}
}

int main()
{
	f();
}

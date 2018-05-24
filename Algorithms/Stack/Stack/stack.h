#ifndef STACK_H
#define STACK_H

template<class Type>
class stack
{
public:
	stack(int Msize):MaxSize(Msize)
	{
		_stack = new Type[Msize];
		top = -1;
	}

	~stack()
	{
		delete[] _stack;
	}

	bool pop(Type& item)
	{
		if (!this->stackempty())
		{
			item = _stack[top--];
			return true;
		}
		
		return false;
	}

	void push(const Type item)
	{
		if (this->stackfull())
			return;
		_stack[++top] = item;
	}

	bool stackempty()
	{
		if (top < 0)
			return true;
		return false;
	}

	bool stackfull()
	{
		if (top >= MaxSize-1)
			return true;
		return false;
	}
private:
	Type* _stack;
	int top;
	int MaxSize;
};


#endif

#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
	stack<int>* s = new stack<int>(20);
	for (int i = 0; i < 30; i++)
	{
		s->push(i);
	}
}
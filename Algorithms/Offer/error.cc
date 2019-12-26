#include <iostream>

void foo(short startIndex)
{
  short buffer[50000] = { 0 };
  short dd = 0;
  for (unsigned short i = startIndex; i < 33000; ++i)
  {
      if(dd < i)
      {   dd = i;
        std::cout << dd << std::endl;
      }
  
    buffer[i] = (char)i;
  }
}


int main()
{
  char a = 'a';
  int b = 0;
  int *pInt1 = &b;
  int c = *pInt1;
  pInt1 = (int*)(&a);
  int *pInt2 = pInt1 + 1;
  int d = *pInt2;

    foo(0);
  return 0;
}
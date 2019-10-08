#include <iostream>

using namespace std;

#define ONE 1
#define FIVE 5
#define TEN 10
#define TWENTYFIVE 25

//找零钱问题
int main()
{
    int total = 401;
    int one = 0, five = 0, ten = 0, twentyfive = 0;

    while (total >= TWENTYFIVE)
    {
        total -= TWENTYFIVE;
        twentyfive ++;
    }

    while (total >= TEN)
    {
        total -= TEN;
        ten ++;
    }

    while (total >= FIVE)
    {
        total -= FIVE;
        five ++;
    }

    while (total >= ONE)
    {
        total -= ONE;
        one ++;
    }
    

    cout << "solution is : " << twentyfive << "  25 cent. " << ten << "  10 cent. "<< five << "  5 cent. " << one << "  1 cent. " << endl;
}
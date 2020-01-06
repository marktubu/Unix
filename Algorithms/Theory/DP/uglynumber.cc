#include <iostream>
#include <vector>
#include <algorithm>

unsigned ugly_number(unsigned n)
{
    std::vector<unsigned> ugly;
    ugly.reserve(n);

    ugly.push_back(1);
    unsigned i2 = 0, i3 = 0, i5 = 0;
    unsigned next_multiple_of_2 = 2;
    unsigned next_multiple_of_3 = 3;
    unsigned next_multiple_of_5 = 5;

    unsigned ugly_no = 1;

    for (size_t i = 1; i < n; i++)
    {
        ugly_no = std::min(next_multiple_of_2, std::min(next_multiple_of_3, next_multiple_of_5));

        ugly.push_back(ugly_no);
        if(ugly_no == next_multiple_of_2)
        {
            i2 = i2 + 1;
            next_multiple_of_2 = ugly[i2] * 2; 
        }
        if(ugly_no == next_multiple_of_3)
        {
            i3 = i3 + 1;
            next_multiple_of_3 = ugly[i3] * 3; 
        }
        if(ugly_no == next_multiple_of_5)
        {
            i5 = i5 + 1;
            next_multiple_of_5 = ugly[i5] * 5; 
        }
    }
    
    return ugly_no;
}

int main()
{
    unsigned ret = ugly_number(150);
    std::cout << "ugly number : " << ret << std::endl;
    return 0;
}
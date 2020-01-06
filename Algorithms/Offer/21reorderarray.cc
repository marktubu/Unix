#include <iostream>

using namespace std;

void reorder(int* pdata, unsigned int length)
{
    if(pdata == nullptr)
        return;
    
    int* pstart = pdata;
    int* pend = pdata + length -1;

    while (pstart < pend)
    {
        while(pstart < pend && ((*pstart) & 0x1) != 0)
        {
            pstart++;
        }

        while(pstart < pend && ((*pend) & 0x1) == 0)
        {
            pend--;
        }

        if(pstart != pend)
        {
            int tmp = *pstart;
            *pstart = *pend;
            *pend = tmp;
        }
        
    }
    
}
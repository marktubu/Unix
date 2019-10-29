#include <iostream>
#include <string.h>
#include <cstdint>
#include <vector>
#include <limits.h>
#include <sstream> 
#include <string>
#include <stdlib.h>
#include <algorithm>    // std::min

using namespace std;

int maxArea(vector<int>& height) 
{
    int max_v = 0;
    pair<int, int> ret;
    for (size_t i = 0; i < height.size(); i++)
    {
        for (size_t j = 0; j != i && j < height.size(); j++)
        {
            int x = abs(int(j-i));
            int h = std::min(height[i], height[j]);
            int v = x * h;
            if(v > max_v)
            {
                max_v = v;
                ret.first = i;
                ret.second = j;
            }
        }
    }
                
    std::cout << "ret pos1: " << ret.first << " pos2: " << ret.second << " max value: " << max_v << std::endl;
    return 0;
}

int main(int argc, char* argv[])
{
    vector<int> s = {2, 10, 4, 9, 5, 5, 4, 2, 1};
    maxArea(s);
    return 0;
}
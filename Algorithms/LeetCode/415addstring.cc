#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string addStrings(string num1, string num2) {
        int length1 = num1.size();
        if(length1 == 0)
            return num2;
        int length2 = num2.size();
        if(length2 == 0)
            return num1;
        
        int length = length1 > length2 ? length1 : length2;
        string ret(length, ' ');
        int index1 = length1 - 1;
        int index2 = length2 - 1;
        int index = length - 1;
        int increment = 0;
        while (index1 >= 0 || index2 >= 0)
        {
            char param1 = 0;
            char param2 = 0;

            if(index1 >= 0)
                param1 = num1[index1] - '0';
            if(index2 >= 0)
                param2 = num2[index2] - '0';

            int sum = param1 + param2 + increment;
            if(sum >= 10)
            {
                sum -= 10;
                increment = 1;
            }
            else
            {
                increment = 0;
            }

            ret[index] = sum + '0';

            index1--;
            index2--;
            index--;
        }
        
        if(increment > 0)
        {
            ret = "1" + ret;
        }
        return ret;
    }
};
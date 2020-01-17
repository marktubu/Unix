#include <iostream>
#include <string>

using namespace std;

string add(string& s1, string& s2)
{
    if(s1.empty())
        return s2;
    if(s2.empty())
        return s1;
    
    int size1 = s1.size();
    int size2 = s2.size();
    int min_len = size1 > size2 ? size2 : size1;
    int max_len = size1 > size2 ? size1 : size2;
    int increment = 0;
    string s(' ', max_len);

    for (size_t i = 0; i < max_len; i++)
    {
        int index1 = max_len - i - 1;
        int index2 = min_len - i - 1;

        char c1 = s1[index1];
        char c2 = s2[index2];

        if(index2 < 0)
        {
            c2 = '0';
        }
        int r1 = c1 - '0';
        int r2 = c2 - '0';

        cout << r1 << "  " << r2 << "  " << increment << "  "  << endl;
        int r = r1 + r2 + increment;
        if(r > 9)
        {
            r -= 10;
            increment = 1;
        }
        else
        {
            increment = 0;
        }

        s[index1] = r + '0';
    }
    
    if(increment > 0)
    {
        s = '1' + s;
    }
    cout << "s : " << s << endl;
    return s; 
}


int main()
{
    string s1("34646313135453431");
    string s2("999999999121111");
    string s = add(s1, s2);
    cout << "result is : " << s << endl;
    return 0;
}
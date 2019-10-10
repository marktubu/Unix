#include <iostream>
#include <string.h>
#include <cstdint>
#include <vector>
#include <limits.h>
#include <sstream> 
#include <string>
#include <cstdlib>

using namespace std;

bool isMatch(string s, string p) 
{
    if(s.empty())
    {
        return p.empty() || (p.length() == 2 && p[1] == '*');
    }

    if(p.empty())
    {
        return false;
    }

    bool first_match = s[0] == p[0] || p[0] == '.';

    if(p.length() >= 2 && p[1] == '*')
    {
        string s_1 = s.substr(1, s.size());  
        string p_2 = p.substr(2, p.size());  
        cout << "s1 " << s_1 << endl;
        return isMatch(s, p_2) || first_match && isMatch(s_1, p);
    }
    else
    {
        string s_1 = s.substr(1, s.size());  
        string p_1 = p.substr(1, p.size()); 
        return first_match && isMatch(s_1, p_1);
    }
}

int main(int argc, char* argv[])
{
    if(argc < 3)
        return 0;
    
    char* arg1 = argv[1];
    char* arg2 = argv[2];
    cout << "arg " << arg1 << "  " << arg2 << endl;
    
    string str1("aa");
    string str2("a*");

    bool ret = isMatch(str1, str2);
    cout << "reverse : " << ret << endl;
    return 0;
}
#include <iostream>
#include <string.h>
#include <cstdint>
#include <vector>
#include <limits.h>
#include <sstream> 
#include <string>
#include <cstdlib>

using namespace std;

enum State
{
    Letter,
    Dot,
    Star
}

bool isMatch(string s, string p) 
{
    
}

int main(int argc, char* argv[])
{
    if(argc < 3)
        return 0;
    
    char* arg1 = argv[1];
    char* arg2 = argv[2];
    cout << "arg " << arg1 << "  " << arg2 << endl;
    
    string str1(arg1);
    string str2(arg2);

    bool ret = isMatch(str1, str2);
    cout << "reverse : " << ret << endl;
    return 0;
}
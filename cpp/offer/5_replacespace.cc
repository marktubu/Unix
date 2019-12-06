#include <iostream>
#include <string>

using namespace std;

string replacespace(string str)
{
    if(str.empty())
        return str;
    
    string ret;
    for (string::iterator it = str.begin(); it != str.end(); it++)
    {
        string::value_type v = *it;
        if(v == ' ')
        {
            ret.append("%20");
        }
        else
        {
            ret.push_back(v);
        }    
    }

    return ret;
}

int main()
{
    string s("We are happy.");
    string ret = replacespace(s);
    cout << "ret : " << ret << endl;
    return 0;
}
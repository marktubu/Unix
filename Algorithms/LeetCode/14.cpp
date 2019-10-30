#include <iostream>
#include <string>
#include <vector>

using namespace std;

string longestCommonPrefix(vector<string>& strs) 
{
    if(strs.size() == 0)
        return "";
    if(strs.size() == 1)
        return strs[0];
    string ret;
    string current = strs[0];
    int i = 0;
    while(i < strs.size()-1)
    {
        ret = "";
        string str1 = current;
        string str2 = strs[i+1];
        string& short_str = str1.length() > str2.length() ? str2 : str1;
        string& long_str = str1.length() > str2.length() ? str1 : str2;

        int end = short_str.length();
        while (end > 0)
        {
            if(long_str.compare(0, end, short_str, 0, end) == 0)
            {
                current = short_str.substr(0, end);
                ret = current;
                break;
            }

            end--;
        }
        
        if(ret == "")
        {
            break;
        }

        i++;
    }

    return ret;
}

int main()
{
    vector<string> strs = {"flower", "flow", "flight"};
    vector<string> strs2 = {"dog","racecar","car"};
    vector<string> strs3 = {"a","a","b"};
    string ret = longestCommonPrefix(strs);
    cout << "longest : " << ret << endl;
    return 0;
}
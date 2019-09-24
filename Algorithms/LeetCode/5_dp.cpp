#include <iostream>
#include <vector>

using namespace std;

string longest(const string& s)
{
    if(s.size() <= 1)
        return s;
    
    uint32_t longest = 1;
    uint32_t len = s.size();

    vector<vector<bool>> dp(len,vector<bool>(len));    

    size_t start_index = 0;

    for (size_t i = 0; i < len; i++)
    {
        dp[i][i] = true;
        if((i < len - 1) && s[i] == s[i+1])
        {
            dp[i][i+1] = true;
            longest = 2;

            if(start_index == 0)
            {
                start_index = i;
            }
        }
    }
  
    for (size_t sz = 3; sz < len + 1; sz++)
    {
        for (size_t i = 0; i <= len - sz; i++)
        {
            size_t start = i;
            size_t end = i + sz - 1;

            if(s[start] == s[end] && dp[start+1][end-1])
            {
                dp[start][end] = true;
                longest = sz;
                start_index = i;
            }
        }
        
    }
    
    return s.substr(start_index, longest);
}

int main()
{

}
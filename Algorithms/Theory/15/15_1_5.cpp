#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int shulie(vector<int>& vec, int n)
{
    if(n>=0)
    {
        vec[0] = 0;
    }
    if(n>=1)
    {
        vec[1] = 1;
    }
    for (size_t i = 2; i <= n; i++)
    {
        vec[i] = vec[i-1] + vec[i-2];
    }
    
    return vec[n];
}

int main()
{
    int n = 15;
    vector<int> vec(n+1, 0);
    int ret = shulie(vec, n);
    cout << "result : " << ret << endl;
    return 0;
}


//0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610
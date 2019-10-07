#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int cut_aux(const vector<int>& p, int n, vector<int>& r)
{
    if(r[n] >= 0)
        return r[n];
    int q = -1;
    if(n == 0)
    {
        q = 0;
    }
    else
    {
        for (size_t i = 1; i <= n; i++)
        {
            q = max(q, p[i] + cut_aux(p, n-i, r));
        }
    }
    
    r[n] = q;
    return q;
}

int cut(const vector<int>& p, int n, vector<int>& r)
{
    return cut_aux(p, n, r);
}

int main()
{
    vector<int> vec{0,1,5,8,9,10,17,18, 28,29,30,31,32,45,50,55,60};
    int n = 12;
    vector<int> r(n+1, -1);
    int ret = cut(vec, n, r);
    cout << "result : " << ret << endl;
    return 0;
}
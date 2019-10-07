#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print_solution(int n, vector<int>& s)
{
    while (n > 0)
    {
        cout << "solution " << s[n] << endl;
        n = n - s[n];
    }
}

int bottom_up_cut(const vector<int>& p, int n,vector<int>& r,vector<int>& s)
{
    r[0] = 0;
    s[0] = 0;
    for (size_t j = 1; j <= n; j++)
    {
        int q = -1;
        for (size_t i = 1; i <= j; i++)
        {
            //q = max(q, p[i] + r[j-i]);
            if(q < p[i] + r[j-i])
            {
                q = p[i] + r[j-i];
                s[j] = i;
            }
        }
        
        r[j] = q;
    }
    
    return r[n];
}

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
    vector<int> s(n+1, -1);
    int ret = cut(vec, n, r);
    ret = bottom_up_cut(vec, n, r, s);
    cout << "result : " << ret << endl;
    print_solution(n, s);
    return 0;
}
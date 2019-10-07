#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int cut(const vector<int>& p, int n)
{
    if(n == 0)
        return 0;
    
    int q = 0;
    for(int i=1;i<=n;i++)
    {
        q = max(q,p[i] + cut(p, n - i));
    }

    return q;
}

int main()
{
    vector<int> vec{1,5,8,9,10,17,18, 20,24,30,35,40,45,50,55,60};
    int ret = cut(vec, 12);
    cout << "result : " << ret << endl;
    return 0;
}
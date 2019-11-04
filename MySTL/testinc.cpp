#include <iostream>
#include <list>

using namespace std;

int main()
{
    list<int> my_list = {1,2,3,4,5};
    list<int>::iterator iter = my_list.begin();

    ++iter;
    iter = my_list.erase(iter);
    my_list.insert(iter, 33);

    for (auto v : my_list)
    {
        cout << "value: " << v << endl;
    }
    

    return 0;
}
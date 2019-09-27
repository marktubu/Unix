#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> find(vector<int> person, vector<int> crossed)
{
    cout << " enter find " << person.size() << endl;
    if(person.size() == 2)
    {
        int time = person[0] > person[1] ? person[0] : person[1];
        return vector<vector<int>>{vector<int>{person[0], person[1], time}};
    }
    
    int totaltime = 10000;
    vector<vector<int>> last_solution;

    for (vector<int>::iterator it = person.begin(); it != person.end(); it++)
    {   
        for (vector<int>::iterator it2 = person.begin(); it2 != person.end(); it2++)
        {   
            if(it2 == it)
                continue;
            vector<vector<int>> solution;

            //过去时间
            int time = *it > *it2 ? *it : *it2;

            //找出返回的人
            vector<int> cross;
            cross.insert(cross.end(), crossed.begin(), crossed.end());
            cross.push_back(*it);
            cross.push_back(*it2);
            int min = 10000;
            vector<int>::iterator toberemoved;
            for (vector<int>::iterator i = cross.begin(); i != cross.end(); i++)
            {
                if(*i < min)
                {
                    toberemoved = i;
                    min = *i;
                }
            }
            
            cross.erase(toberemoved);

            vector<int> pers;
            
            pers.insert(pers.end(), person.begin(), person.end());
            for (vector<int>::iterator i = pers.begin(); i != pers.end(); i++)
            {
                //cout << " erase " << person.size() << "   " << *i << endl;
                if(*i == *it || *i == *it2)
                {
                    pers.erase(i);
                    i--;
                }
            }

            pers.push_back(min);

            solution.push_back(vector<int>{*it, *it2, time + min});
            
            auto vec = find(pers, cross);
            solution.insert(solution.end(), vec.begin(), vec.end());

            int total = 0;
            for (vector<vector<int>>::iterator i = solution.begin(); i != solution.end(); i++)
            {
                total += (*i)[2];
                if(person.size() == 4)
                    cout << "solution " << person.size() << "  " << (*i)[0] <<"  " <<(*i)[1] << "   " << (*i)[2] << endl;
            }
            if(person.size() == 4)
                cout << "total time : " << total << endl;
            if(total < totaltime)
            {
                totaltime = total;
                last_solution = solution;
            }
        }
    }

    return last_solution;
}

int main()
{
    vector<int> person{1, 2, 5, 10, 6, 12};
    vector<int> crossed;

    vector<vector<int>> solution = find(person, crossed);

    for (vector<vector<int>>::iterator i = solution.begin(); i != solution.end(); i++)
    {
        cout << "person 1 " << (*i)[0] << " person 2 " << (*i)[1] << " time " << (*i)[2] << endl;
    }

}
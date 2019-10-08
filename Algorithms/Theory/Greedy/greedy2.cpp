#include <iostream>
#include <vector>

using namespace std;

typedef struct object
{
    int weight;
    int value;
    int status;
} OBJECT;

typedef struct problem
{
    vector<OBJECT> objs;
    int solution;
} PROBLEM;

int chooseMethod(vector<OBJECT>& objs)
{
    int index = -1;
    float max_midu = 0;

    for (size_t i = 0; i < objs.size(); i++)
    {
        OBJECT obj = objs[i];
        if(obj.status == 0)
        {
            float midu = obj.value / obj.weight;
            if(midu > max_midu)
            {
                max_midu = midu;
                index = i;
            }
        }
    }
    
    return index;
}

void mainProcess(PROBLEM& problem, int c)
{
    int idx = -1;
    int current_weight = 0;

    while (idx = chooseMethod(problem.objs) != -1)
    {
        OBJECT obj = problem.objs[idx];
        if(obj.weight + current_weight <= c)
        {
            obj.status = 1;
            current_weight += obj.weight;
        }
        else
        {
            obj.status = 2;
        }
    }

    print_solution(problem);
}

void print_solution(PROBLEM& problem)
{
    for (size_t i = 0; i < problem.objs.size(); i++)
    {
        cout << "status " << i << "    " << problem.objs[i].status << endl;
    }
}

int main()
{
    vector<int> weights = {35,30,60,50,40,10,25};
    vector<int> values = {10,40,30,50,35,40,30};

    PROBLEM problem;
    problem.objs = {{35,10,0},{30,40,0},{60,30,0},{50,50,0},{40,35,0},{10,40,25},{35,10,30}};
    problem.solution = 0;

    mainProcess(problem, 150);

    return 0;
}
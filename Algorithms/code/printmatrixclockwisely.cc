#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> printMatrixInCircle(const vector<vector<int> >& matrix, int columns, int rows, int start)
    {
        int endx = columns - start - 1;
        int endy = rows - start - 1;

        vector<int> ret;

        if(start == endx)
        {
            for (size_t i = start; i <= endy; i++)
            {
                ret.push_back(matrix[i][start]);
            }
            return ret;
        }

        if(start == endy)
        {
            for (size_t i = start; i <= endx; i++)
            {
                ret.push_back(matrix[endy][i]);
            }
            return ret;
        }

        for (size_t i = start; i < endx; ++i)
        {
            int num = matrix[start][i];
            ret.push_back(num);
        }

        for (size_t i = start; i < endy; ++i)
        {
            int num = matrix[i][endx];
            ret.push_back(num);
        }
        
        for (size_t i = endx; i > start; --i)
        {
            int num = matrix[endy][i];
            ret.push_back(num);
        }
        
        for (size_t i = endy; i > start; --i)
        {
            int num = matrix[i][start];
            ret.push_back(num);
        }

        return ret;
    }

    vector<int> printMatrix(vector<vector<int> > matrix) {
        vector<int> ret;
        if(matrix.size() == 0)
            return ret;
        
        int rows = matrix.size();
        int columns = matrix[0].size();

        int start = 0;
        while (columns > start * 2 && rows > start * 2)
        {
            vector<int> result = printMatrixInCircle(matrix, columns, rows, start);
            ret.insert(ret.end(), result.begin(), result.end());
            ++start;
        }
        
        return ret;
    }
};


int main()
{
    Solution so;
    vector<vector<int> > matrix = {{1, 2, 3, 4,}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    vector<int> ret = so.printMatrix(matrix);

    for (vector<int>::iterator it = ret.begin(); it != ret.end(); ++it)
    {
        std::cout << "ret : " << *it << std::endl;
    }
    
}
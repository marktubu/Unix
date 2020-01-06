#include <iostream>
#include <stack>

using namespace std;

bool find(int* matrix, int rows, int columes, int number)
{
    if(matrix == NULL)
        return false;
    
    int min = matrix[0];
    if(number < min)
        return false;
    int max = matrix[rows * columes - 1];
    if(number > max)
        return false;
    
    int row = 0;
    int col = columes - 1;
    int min_row = row;
    int max_col = col;
    while (1)
    {
        int val = matrix[row * columes + col];
        if(val == number)
        {
            cout << "row col : " << row << "  " << col << endl;
            return true;
        }    
        else if(val < number)
        {
            row++;
            min_row ++;
        }
        else
        {
            col--;
            max_col--;
        }
        
        if(col < 0 || row > rows - 1)
            return false;
    }
    
}

int main()
{
    int matrix[][4] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};
    bool ret = find((int*)matrix, 4, 4, 7);
    cout << "result : " << ret << endl;
}
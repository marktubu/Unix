#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<vector<int> > Grid;

const int GRID_SIZE = 9;

bool Is9GridCorrect(Grid& grid, int row, int col)
{
    vector<int> check(GRID_SIZE, 0);
    int zero_count = 0;
    for (size_t i = row; i < row+3; i++)
    {
        for (size_t j = col; j < col+3; j++)
        {
            int value = grid[row][col];
            if(value == 0)
            {
                zero_count ++;
            }
            else
            {
                check[value] = 1;
            }
        }
    }
    
    int count = 0;
    for (size_t i = 0; i < check.size(); i++)
    {
        count += check[i];
    }
    
    bool correct = count + zero_count == GRID_SIZE;
    return correct;
}

bool IsCorrect(Grid& grid, int row, int col)
{
    int left_bottom_row = row - 2;
    int left_bottom_col = col - 2;
    int right_top_row = row + 2;
    int right_top_col = col + 2;

    left_bottom_row = max(left_bottom_row, 0);
    left_bottom_col = max(left_bottom_col, 0);

    right_top_row = min(right_top_row, GRID_SIZE - 1);
    right_top_col = min(right_top_col, GRID_SIZE - 1);

    for (size_t i = left_bottom_row; i <= right_top_row - 2; i++)
    {
        for (size_t j = left_bottom_col; j <= right_top_col - 2; j++)
        {
            
        }
        
    }
    
}

bool Sudoku(Grid& grid, int row, int col)
{

}

void PrintSolution(Grid& grid)
{

}

int main()
{
    return 0;
}
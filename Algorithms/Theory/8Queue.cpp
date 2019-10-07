#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int> > Grid;
const int GRID_SIZE = 8;

void PlaceQueue(Grid& grid, int row, int col)
{
    grid[row][col] = 1;
}

void RemoveQueue(Grid& grid, int row, int col)
{
    grid[row][col] = 0;
}

bool IsSafe(Grid& grid, int row, int col)
{
    //check row
    for (size_t i = 0; i < GRID_SIZE; i++)
    {
        if(grid[i][col] == 1)
        {
            return false;
        }
    }
    
    //check colume
    for (size_t i = 0; i < GRID_SIZE; i++)
    {
        if(grid[row][i] == 1)
        {
            return false;
        }
    }
    
    //check left bottom
    int current_row = row;
    int current_col = col;
    while (--current_row >=0 && --current_col >= 0)
    {
        if(grid[current_row][current_col] == 1)
        {
            return false;
        }
    }
    
    //check left top
    current_row = row;
    current_col = col;
    while (--current_row >= 0 && ++current_col < GRID_SIZE)
    {
        if(grid[current_row][current_col] == 1)
        {
            return false;
        }
    }
    
    return true;
}

bool NQueue(Grid& grid, int colume)
{
    if(colume == GRID_SIZE)
    {
        return true;
    }

    for (size_t i = 0; i < GRID_SIZE; i++)
    {
        if(IsSafe(grid, colume, i))
        {
            PlaceQueue(grid, colume, i);
            bool success = NQueue(grid, colume + 1);
            if(success)
            {
                return true;
            }
            else
            {
                RemoveQueue(grid, colume, i);
                continue;
            }
        }
    }
    
    return false;
}

void PrintSolution(Grid& grid)
{
    for (size_t i = 0; i < GRID_SIZE; i++)
    {
        for (size_t j = 0; j < GRID_SIZE; j++)
        {
            if(grid[i][j] == 1)
            {
                cout << "Solution row : colume " << i << "  " << j << endl;
            }
        }
    }
}

int main()
{
    vector<vector<int> > grid(GRID_SIZE, vector<int>(GRID_SIZE, 0));
    if(NQueue(grid, 0))
    {
        PrintSolution(grid);
    }
    else
    {
        cout << "No Solution Found" << endl;
    }
    
    return 0;
}

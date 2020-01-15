#include <iostream>

using namespace std;

void PrintMatrixInCircle(int** matrix, int columns, int rows, int start)
{
    for (size_t i = start; i < columns - start - 1; i++)
    {
        int index = start * columns + i;
        cout << "matrix " << i << " : " << matrix[index] << endl; 
    }
    
    for (size_t i = start; i < rows - start - 1; i++)
    {
        int index = i * rows + columns - start - 1;
        cout << "matrix " << i << " : " << matrix[index] << endl; 
    }
}

void PrintMatrixClockwisely(int** matrix, int columns, int rows)
{
    if(matrix == nullptr || columns == 0 || rows == 0)
    {
        return;
    }

    int start = 0;
    while(columns > start * 2 && rows > start * 2)
    {
        PrintMatrixInCircle(matrix, columns, rows, start);
        ++start;
    }
    
}
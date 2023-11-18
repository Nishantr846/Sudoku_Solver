#include <iostream>
#include <cmath> // Include the cmath header for the sqrt function

using namespace std;

// Function to print the Sudoku grid
void printGrid(int **grid, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if it's safe to place a number at a given position
bool isSafe(int **grid, int row, int col, int num, int N)
{
    // Check if 'num' is not already present in the current row and column
    for (int x = 0; x < N; x++)
    {
        if (grid[row][x] == num || grid[x][col] == num)
        {
            return false;
        }
    }

    // Check if 'num' is not already present in the current subgrid
    int sqrtN = (int)sqrt(N);
    int startRow = row - row % sqrtN;
    int startCol = col - col % sqrtN;
    for (int i = 0; i < sqrtN; i++)
    {
        for (int j = 0; j < sqrtN; j++)
        {
            if (grid[i + startRow][j + startCol] == num)
            {
                return false;
            }
        }
    }

    // If 'num' is not present in the row, column, and subgrid, it's safe
    return true;
}

// Main Sudoku solving function using backtracking
bool solveSudoku(int **grid, int N)
{
    int row, col;

    // Find the first empty cell
    bool isEmpty = false;
    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
        {
            if (grid[row][col] == 0)
            {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty)
        {
            break;
        }
    }

    // If there are no empty cells, the Sudoku is solved
    if (!isEmpty)
    {
        return true;
    }

    // Try filling the empty cell with numbers from 1 to N
    for (int num = 1; num <= N; num++)
    {
        if (isSafe(grid, row, col, num, N))
        {
            grid[row][col] = num;

            // Recursively try to solve the rest of the Sudoku
            if (solveSudoku(grid, N))
            {
                return true;
            }

            // If the current placement doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    // If no number can be placed in the current cell, return false
    return false;
}

int main()
{
    int N;
    cout << "Enter the dimension of Sudoku (e.g., 4, 6, 9): ";
    cin >> N;

    int **grid = new int *[N];
    for (int i = 0; i < N; i++)
    {
        grid[i] = new int[N];
    }

    cout << "Enter the Sudoku puzzle (use 0 for empty cells):\n";

    // Accept input from the user
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> grid[i][j];
        }
    }

    if (solveSudoku(grid, N))
    {
        cout << "Sudoku Solution:" << endl;
        printGrid(grid, N);
    }
    else
    {
        cout << "No solution exists." << endl;
    }

    for (int i = 0; i < N; i++)
    {
        delete[] grid[i];
    }
    delete[] grid;

    return 0;
}

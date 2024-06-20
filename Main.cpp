#include <iostream>
#include <vector>

using namespace std;

#define UNASSIGNED '*'
#define N 9

bool isSafe(vector<vector<char>>& grid, int row, int col, char num);
bool solveSudoku(vector<vector<char>>& grid);
bool findUnassignedLocation(vector<vector<char>>& grid, int &row, int &col);
void printGrid(vector<vector<char>>& grid);

// Function to find an unassigned location in the grid
bool findUnassignedLocation(vector<vector<char>>& grid, int &row, int &col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == UNASSIGNED) {
                return true;
            }
        }
    }
    return false;
}

// Function to check if num can be placed in grid[row][col]
bool isSafe(vector<vector<char>>& grid, int row, int col, char num) {
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}

// Function to solve the Sudoku using backtracking
bool solveSudoku(vector<vector<char>>& grid) {
    int row, col;
    if (!findUnassignedLocation(grid, row, col)) {
        return true; // success!
    }

    for (char num = '1'; num <= '9'; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) {
                return true;
            }
            grid[row][col] = UNASSIGNED;
        }
    }
    return false; // triggers backtracking
}

// Function to print the grid
void printGrid(vector<vector<char>>& grid) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<char>> grid(N, vector<char>(N));

    cout << "Enter the Sudoku grid (use * for unfilled cells):" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }

    if (solveSudoku(grid)) {
        cout << "Solved Sudoku grid:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists" << endl;
    }

    return 0;
}

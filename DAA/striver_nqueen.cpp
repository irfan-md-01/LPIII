#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool safe(int r, int c, vector<string> &board) {
        int row = r, col = c;

        // Check upper-left diagonal
        while (row >= 0 && col >= 0) {
            if (board[row][col] == 'Q') return false;
            row--; col--;
        }

        // Reset row, check left side in the same row
        row = r, col = c;
        while (col >= 0) {
            if (board[row][col] == 'Q') return false;
            col--;
        }

        // Reset column, check lower-left diagonal
        row = r, col = c;
        while (row < board.size() && col >= 0) {
            if (board[row][col] == 'Q') return false;
            row++; col--;
        }

        return true;
    }

    void help(int col, int n, int k, int placedQueens, 
              vector<string> &board, vector<vector<string>> &ans) {
        if (placedQueens == k) {            // Exactly k queens are placed
            ans.push_back(board);
            return;
        }
        if (col == n) return;              // All columns used up

        for (int row = 0; row < n; row++) {
            if (safe(row, col, board)) {
                board[row][col] = 'Q';
                help(col + 1, n, k, placedQueens + 1, board, ans);
                board[row][col] = '.';
            }
        }

        // Option to skip this column without placing a queen (only if more queens can be placed later)
        help(col + 1, n, k, placedQueens, board, ans);
    }

    vector<vector<string>> solveKQueens(int n, int k, int i, int j) {
        vector<vector<string>> ans;
        vector<string> board(n, string(n, '.'));
        board[i][j] = 'Q';
        help(0, n, k-1, 0, board, ans);
        return ans;
    }
};

int main() {
    int n, k;
    cout << "Enter the size of the board (n x n): ";
    cin >> n;
    cout << "Enter the number of queens to place: ";
    cin >> k;

    if (k > n) {
        cout << "Number of queens cannot exceed board size!" << endl;
        return 0;
    }
    
    int r1, c1; // 1-indexed input for user convenience
    cout << "Enter position of the first Queen (row col) [1-indexed]: ";
    cin >> r1 >> c1;

    // Convert to 0-indexed and validate
    int fixedRow = r1 - 1, fixedCol = c1 - 1;
    // if (N <= 0 || fixedRow < 0 || fixedRow >= N || fixedCol < 0 || fixedCol >= N) {
    //     cout << "Invalid input.\n";
    //     return 0;
    // }

    cout << "\nSolving using backtracking with first queen fixed at ("
         << r1 << ", " << c1 << "):\n";
         
         
    Solution obj;
    vector<vector<string>> solutions = obj.solveKQueens(n, k, fixedRow, fixedCol  );

    if (solutions.empty()) {
        cout << "No solutions exist!" << endl;
    } else {
        cout << "Number of solutions: " << solutions.size() << "\n\n";
        for (auto &board : solutions) {
            for (auto &row : board) {
                cout << row << endl;
            }
            cout << "\n";
        }
    }
    return 0;
}

// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
#include <vector>
using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE];

// Function to initialize the board with numbers 1-9
void initializeBoard() {
    char pos = '1';
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = pos++;
}

// Function to print the current board
void printBoard() {
    cout << "\nCurrent board:\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << " " << board[i][j];
            if (j < SIZE - 1) cout << " |";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "---+---+---\n";
    }
    cout << "\n";
}

// Function to check for a winner or tie
char checkWinner() {
    // Rows and Columns
    for (int i = 0; i < SIZE; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }

    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];

    // Check for tie
    bool full = true;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                full = false;

    if (full)
        return 'T'; // Tie

    return ' '; // Game still going
}

// Convert cell number (1-9) to board coordinates
bool getCoordinates(int cell, int &row, int &col) {
    if (cell < 1 || cell > 9) return false;
    row = (cell - 1) / SIZE;
    col = (cell - 1) % SIZE;
    return true;
}

// Function to get a valid move from the current player
int getValidMove(char currentPlayer) {
    int move;
    while (true) {
        cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        if (!(cin >> move)) {
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        int row, col;
        if (!getCoordinates(move, row, col)) {
            cout << "Move out of bounds. Please enter a number between 1 and 9.\n";
            continue;
        }

        if (board[row][col] == 'X' || board[row][col] == 'O') {
            cout << "That cell is already taken. Choose another.\n";
            continue;
        }

        return move;
    }
}

int main() {
    cout << "Welcome to Tic-Tac-Toe!\nPlayer 1 is 'X' and Player 2 is 'O'\n";
    initializeBoard();

    char currentPlayer = 'X';
    char winner = ' ';

    while (winner == ' ') {
        printBoard();
        int move = getValidMove(currentPlayer);
        int row, col;
        getCoordinates(move, row, col);
        board[row][col] = currentPlayer;

        winner = checkWinner();
        if (winner != ' ')
            break;

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    printBoard();
    if (winner == 'T') {
        cout << "It's a tie!\n";
    } else {
        cout << "Player " << winner << " wins!\n";
    }

    cout << "Game over. Thanks for playing!\n";
    return 0;
}


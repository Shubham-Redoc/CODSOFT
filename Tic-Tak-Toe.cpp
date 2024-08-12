#include <iostream>

using namespace std;

char board[3][3];  // 3x3 grid for the game
char currentPlayer = 'X';  // X always starts first

// Function prototypes
void initializeBoard();
void displayBoard();
bool isMoveValid(int row, int col);
void makeMove(int row, int col);
bool checkWin();
bool checkDraw();
void switchPlayer();

int main() {
    char playAgain;
    do {
        initializeBoard();
        bool gameWon = false;
        bool gameDraw = false;

        while (!gameWon && !gameDraw) {
            displayBoard();
            int row, col;
            cout << "Player " << currentPlayer << ", enter your move (row and column): ";
            cin >> row >> col;

            if (isMoveValid(row, col)) {
                makeMove(row, col);
                gameWon = checkWin();
                if (!gameWon) {
                    gameDraw = checkDraw();
                    if (!gameDraw) {
                        switchPlayer();
                    }
                }
            } else {
                cout << "Invalid move. Try again." << endl;
            }
        }

        displayBoard();

        if (gameWon) {
            cout << "Player " << currentPlayer << " wins!" << endl;
        } else if (gameDraw) {
            cout << "It's a draw!" << endl;
        }

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}

// Initialize the game board with empty spaces
void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// Display the current state of the board
void displayBoard() {
    cout << "  0 1 2" << endl;
    for (int i = 0; i < 3; i++) {
        cout << i << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << "|";
        }
        cout << endl;
        if (i < 2) cout << "  -----" << endl;
    }
}

// Check if the move is valid
bool isMoveValid(int row, int col) {
    return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ');
}

// Update the board with the current player's move
void makeMove(int row, int col) {
    board[row][col] = currentPlayer;
}

// Check if the current player has won
bool checkWin() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
            (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
        (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)) {
        return true;
    }

    return false;
}

// Check if the game is a draw
bool checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false;  // There is still an empty space, so no draw
            }
        }
    }
    return true;  // No empty spaces left, so it's a draw
}

// Switch to the next player
void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

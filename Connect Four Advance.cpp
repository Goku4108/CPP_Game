#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int ROWS = 6;
const int COLS = 7;
const char EMPTY = ' ';
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';


void printBoard(const vector<vector<char>>& board) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << "| " << board[i][j] << " ";
        }
        cout << "|\n";
    }
    cout << "-----------------------------\n";
    cout << "| 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n";
    cout << "-----------------------------\n";
}

bool isValidMove(const vector<vector<char>>& board, int col) {
    return col >= 0 && col < COLS && board[0][col] == EMPTY;
}


void makeMove(vector<vector<char>>& board, int col, char player) {
    for (int i = ROWS - 1; i >= 0; --i) {
        if (board[i][col] == EMPTY) {
            board[i][col] = player;
            break;
        }
    }
}


bool isBoardFull(const vector<vector<char>>& board) {
    for (int j = 0; j < COLS; ++j) {
        if (board[0][j] == EMPTY) {
            return false;
        }
    }
    return true;
}


bool checkWin(const vector<vector<char>>& board, char player) {
    // Check horizontal win
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS - 3; ++j) {
            if (board[i][j] == player && board[i][j + 1] == player &&
                board[i][j + 2] == player && board[i][j + 3] == player) {
                return true;
            }
        }
    }

   
    for (int i = 0; i < ROWS - 3; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (board[i][j] == player && board[i + 1][j] == player &&
                board[i + 2][j] == player && board[i + 3][j] == player) {
                return true;
            }
        }
    }

    
    for (int i = 3; i < ROWS; ++i) {
        for (int j = 0; j < COLS - 3; ++j) {
            if (board[i][j] == player && board[i - 1][j + 1] == player &&
                board[i - 2][j + 2] == player && board[i - 3][j + 3] == player) {
                return true;
            }
        }
    }

    
    for (int i = 0; i < ROWS - 3; ++i) {
        for (int j = 0; j < COLS - 3; ++j) {
            if (board[i][j] == player && board[i + 1][j + 1] == player &&
                board[i + 2][j + 2] == player && board[i + 3][j + 3] == player) {
                return true;
            }
        }
    }

    return false;
}


int getComputerMove(const vector<vector<char>>& board) {
    vector<int> validCols;
    for (int j = 0; j < COLS; ++j) {
        if (isValidMove(board, j)) {
            validCols.push_back(j);
        }
    }
    return validCols[rand() % validCols.size()];
}


int gameMenu() {
    cout << "Game Menu:\n";
    cout << "1. Play again\n";
    cout << "2. Switch to Player vs Player\n";
    cout << "3. Switch to Player vs Computer\n";
    cout << "4. Quit\n";
    int choice;
    cin >> choice;
    return choice;
}

int main() {
    vector<vector<char>> board(ROWS, vector<char>(COLS, EMPTY));
    bool player1Turn = true;
    bool vsComputer = false;

    cout << "Welcome to Connect 4!\n";

    
    while (true) {
        cout << "Select Game Mode:\n1. Player vs Player\n2. Player vs Computer\n";
        int gameMode;
        cin >> gameMode;

        if (gameMode == 1) {
            vsComputer = false;
        } else if (gameMode == 2) {
            vsComputer = true;
        } else {
            cout << "Invalid choice. Please choose 1 or 2.\n";
            continue;
        }
        break;
    }

    srand(static_cast<unsigned int>(time(0))); 

    while (true) {
        
        board.assign(ROWS, vector<char>(COLS, EMPTY));
        player1Turn = true;

        
        while (true) {
            printBoard(board);

            char currentPlayer = (player1Turn) ? PLAYER1 : PLAYER2;
            int col;

            if (vsComputer && !player1Turn) {
                
                cout << "Computer's turn...\n";
                col = getComputerMove(board);
            } else {
                
                cout << "Player " << currentPlayer << ", enter your move (1-7): ";
                cin >> col;

                if (cin.fail() || col < 1 || col > 7) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid input. Please enter a number between 1 and 7.\n";
                    continue;
                }

                col--; 
            }

            if (isValidMove(board, col)) {
                makeMove(board, col, currentPlayer);

                if (checkWin(board, currentPlayer)) {
                    printBoard(board);
                    cout << "Player " << currentPlayer << " wins!\n";
                    break;
                }

                if (isBoardFull(board)) {
                    printBoard(board);
                    cout << "It's a tie!\n";
                    break;
                }

                player1Turn = !player1Turn; 
            } else {
                cout << "Invalid move. Try again.\n";
            }
        }

        
        int choice = gameMenu();
        if (choice == 1) {
            
        } else if (choice == 2) {
            vsComputer = false; 
        } else if (choice == 3) {
            vsComputer = true; 
        } else if (choice == 4) {
            cout << "Thanks for playing! Goodbye!\n";
            break;
        }
    }

    return 0;
}

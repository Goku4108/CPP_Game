#include <iostream>
#include <vector>
using namespace std;

void printBoard(const vector<vector<char>> &board)
{
    int size = board.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << board[i][j];
            if (j < size - 1)
                cout << " | ";
        }
        cout << endl;
        if (i < size - 1)
        {
            for (int k = 0; k < size; k++)
            {
                cout << "---";
                if (k < size - 1)
                    cout << "+";
            }
            cout << endl;
        }
    }
    cout << endl;
}

bool checkThreeInLine(const vector<char> &line)
{
    for (size_t i = 0; i + 2 < line.size(); i++)
    {
        if (line[i] != ' ' && line[i] == line[i + 1] && line[i + 1] == line[i + 2])
        {
            return true;
        }
    }
    return false;
}

bool checkWin(const vector<vector<char>> &board)
{
    int size = board.size();

    for (int i = 0; i < size; i++)
    {
        if (checkThreeInLine(board[i]))
            return true;
    }

    for (int i = 0; i < size; i++)
    {
        vector<char> column(size);
        for (int j = 0; j < size; j++)
        {
            column[j] = board[j][i];
        }
        if (checkThreeInLine(column))
            return true;
    }

    for (int start = 0; start <= size - 3; start++)
    {
        vector<char> mainDiagonal, antiDiagonal;
        for (int i = 0; i + start < size; i++)
        {
            mainDiagonal.push_back(board[i][i + start]);
            antiDiagonal.push_back(board[i][size - 1 - i - start]);
        }
        if (checkThreeInLine(mainDiagonal) || checkThreeInLine(antiDiagonal))
            return true;
    }

    for (int start = 1; start <= size - 3; start++)
    {
        vector<char> mainDiagonal, antiDiagonal;
        for (int i = 0; i + start < size; i++)
        {
            mainDiagonal.push_back(board[start + i][i]);
            antiDiagonal.push_back(board[start + i][size - 1 - i]);
        }
        if (checkThreeInLine(mainDiagonal) || checkThreeInLine(antiDiagonal))
            return true;
    }

    return false;
}

bool checkTie(const vector<vector<char>> &board)
{
    int size = board.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

void resetBoard(vector<vector<char>> &board)
{
    int newSize = board.size() + 1;
    board.clear();
    board.resize(newSize, vector<char>(newSize, ' '));
}

int main()
{
    int initialSize = 3;
    vector<vector<char>> board(initialSize, vector<char>(initialSize, ' '));
    char currentPlayer = 'X';
    int row, col;

    while (true)
    {
        printBoard(board);
        cout << "Player " << currentPlayer << ", enter your move (row and column): ";
        cin >> row >> col;

        int boardSize = static_cast<int>(board.size());

        if (row < 1 || col < 1 || row > boardSize || col > boardSize || board[row - 1][col - 1] != ' ')
        {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        board[row - 1][col - 1] = currentPlayer;

        if (checkWin(board))
        {
            printBoard(board);
            cout << "Player " << currentPlayer << " wins!" << endl;
            break;
        }
        else if (checkTie(board))
        {
            cout << "The game is a tie! Expanding the board..." << endl;
            resetBoard(board);
        }
        else
        {

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    return 0;
}

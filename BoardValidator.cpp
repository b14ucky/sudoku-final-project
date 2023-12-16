#include "BoardValidator.h"

// private functions
bool BoardValidator::checkRow(int board[9][9], int row)
{
    int spottedRows[10]{};
    for (int i = 0; i < 9; i++)
    {
        if (board[row][i] != 0 && spottedRows[board[row][i]] == 0)
        {
            spottedRows[board[row][i]] = 1;
        }
        else if (board[row][i] != 0 && spottedRows[board[row][i]] == 1)
        {
            return false;
        }
    }
    return true;
}

bool BoardValidator::checkColumn(int board[9][9], int column)
{
    int spottedColumns[10]{};
    for (int i = 0; i < 9; i++)
    {
        if (board[i][column] != 0 && spottedColumns[board[i][column]] == 0)
        {
            spottedColumns[board[i][column]] = 1;
        }
        else if (board[i][column] != 0 && spottedColumns[board[i][column]] == 1)
        {
            return false;
        }
    }
    return true;
}

// public functions
bool BoardValidator::checkSquare(int board[9][9], int row, int column)
{
    int spottedSquare[10]{};
    for (int i = row; i < row + 3; i++)
    {
        for (int j = column; j < column + 3; j++)
        {
            if (board[i][j] != 0 && spottedSquare[board[i][j]] == 0)
            {
                spottedSquare[board[i][j]] = 1;
            }
            else if (board[i][j] != 0 && spottedSquare[board[i][j]] == 1)
            {
                return false;
            }
        }
    }
    return true;
}

bool BoardValidator::checkBoard(int board[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        if (!checkRow(board, i))
            return false;
        if (!checkColumn(board, i))
            return false;
        if (i % 3 == 0)
        {
            for (int j = 0; j < 9; j += 3)
            {
                if (!checkSquare(board, i, j))
                    return false;
            }
        }
    }
    return true;
}
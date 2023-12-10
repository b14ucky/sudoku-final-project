#include "validate.h"

bool Validate::checkBoard(int board[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        int spottedRows[10]{};
        int spottedColumns[10]{};
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != 0 && spottedRows[board[i][j]] == 0)
            {
                spottedRows[board[i][j]] = 1;
            }
            else if (board[i][j] != 0 && spottedRows[board[i][j]] == 1)
            {
                return false;
            }
        }
        for (int j = 0; j < 9; j++)
        {
            if (board[j][i] != 0 && spottedColumns[board[j][i]] == 0)
            {
                spottedColumns[board[j][i]] = 1;
            }
            else if (board[j][i] != 0 && spottedColumns[board[j][i]] == 1)
            {
                return false;
            }
        }
    }
    for (int i = 0; i < 9; i += 3)
    {
        for (int j = 0; j < 9; j += 3)
        {
            int spottedSquare[10]{};
            for (int k = i; k < i + 3; k++)
            {
                for (int l = j; l < j + 3; l++)
                {
                    if (board[k][l] != 0 && spottedSquare[board[k][l]] == 0)
                    {
                        spottedSquare[board[k][l]] = 1;
                    }
                    else if (board[k][l] != 0 && spottedSquare[board[k][l]] == 1)
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
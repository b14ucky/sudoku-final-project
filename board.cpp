#include <iostream>
#include <iomanip>

#include "board.h"
#include "validate.h"
#include "functions.h"

using namespace std;

Functions functions;
Validate validate;

Board::Board()
{
    generateBoard();
}

void Board::printBoard()
{
    cout << "   A.  B.  C.  D.  E.  F.  G.  H.  I." << endl;
    for (int i = 0; i < 9; i++)
    {
        cout << i + 1 << ". ";
        for (int j = 0; j < 9; j++)
        {
            if (j == 8)
                if (board[i][j] == 0)
                    cout << " ";
                else
                    cout << board[i][j];
            else if (board[i][j] == 0)
                cout << "  | ";
            else
                cout << board[i][j] << " | ";
        }
        if (i == 8)
            cout << endl;
        else
        {
            cout << endl;
            cout << setw(38);
            cout.fill('-');
            cout << "" << endl;
        }
    }
}

void Board::fillDiagonal()
{
    for (int i = 0; i < 9; i += 3)
    {
        for (int j = i; j < 3 + i; j++)
        {
            for (int k = i; k < 3 + i; k++)
            {
                do
                {
                    board[j][k] = rand() % 9 + 1;
                } while (!validate.checkSquare(board, i, i));
            }
        }
    }
}

bool Board::fillRemaining(int i, int j)
{
    if (j >= 9 && i < 9 - 1)
    {
        i++;
        j = 0;
    }
    if (i >= 9 && j >= 9)
    {
        return true;
    }
    if (i < 3)
    {
        if (j < 3)
        {
            j = 3;
        }
    }
    else if (i < 6)
    {
        if (j == (int)(i / 3) * 3)
        {
            j += 3;
        }
    }
    else
    {
        if (j == 6)
        {
            i++;
            j = 0;
            if (i >= 9)
            {
                return true;
            }
        }
    }
    for (int num = 1; num <= 9; num++)
    {
        board[i][j] = num;
        if (validate.checkBoard(board))
        {
            if (fillRemaining(i, j + 1))
            {
                return true;
            }
        }
        board[i][j] = 0;
    }
    return false;
}

void Board::removeFields()
{
    int count = 0;
    while (count < 40)
    {
        int row = rand() % 9;
        int column = rand() % 9;
        if (board[row][column] != 0)
        {
            count++;
            board[row][column] = 0;
        }
    }
}

void Board::generateBoard()
{
    // generate diagonall boxes
    fillDiagonal();
    // generate rest of the board
    fillRemaining(0, 3);
    // remove some fields from the board to make it playable
    removeFields();
}

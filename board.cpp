#include <iostream>
#include <iomanip>

#include "board.h"
#include "validate.h"

using namespace std;

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

void Board::generateBoard()
{
    Validate validate;
    int tab[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            do
            {
                board[i][j] = tab[rand() % 13];
            } while (!validate.checkBoard(board));
        }
    }
}
#pragma once

class BoardValidator
{
private:
    static bool checkRow(int board[9][9], int row);
    static bool checkColumn(int board[9][9], int col);

public:
    static bool checkSquare(int board[9][9], int row, int col);
    static bool checkBoard(int board[9][9]);
};
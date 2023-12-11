class Validate
{
public:
    bool checkBoard(int board[9][9]);
    bool checkRow(int board[9][9], int row);
    bool checkColumn(int board[9][9], int column);
    bool checkSquare(int board[9][9], int row, int column);
};
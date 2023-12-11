class Board
{
public:
    int board[9][9]{};
    void printBoard();
    void generateBoard();
    void fillDiagonal();
    bool fillRemaining(int i, int j);
    void removeFields();

    Board();
};
#include "Board.h"
#include <iostream>

// private functions
void Board::initBoard()
{
    /*
        Call the board generating algorithm to generate a valid board.
        Then remove 35 fields from the board to make it playable.
    */
    this->fillDiagonal();

    this->fillRemaining(0, 3);

    this->removeFields();
}

void Board::fillDiagonal()
{
    /*
        Fill the diagonal 3x3 squares with random numbers.
    */
    for (int i = 0; i < 9; i += 3)
    {
        for (int j = i; j < 3 + i; j++)
        {
            for (int k = i; k < 3 + i; k++)
            {
                do
                {
                    this->grid[j][k] = rand() % 9 + 1;
                } while (!this->validator.checkSquare(this->grid, i, i));
                this->solution[j][k] = this->grid[j][k];
            }
        }
    }
}

bool Board::fillRemaining(int i, int j)
{
    /*
        Recursive function to fill the remaining fields of the board.
        It starts at the top left corner and fills the board row by row.
        If the function reaches the end of the board, it returns true.
        If the function reaches the end of a row, it goes to the next row.
        If the function reaches the end of a 3x3 square, it goes to the next 3x3 square.
        If the function reaches the end of the board without finding a valid number, it returns false.
        @param i: the row of the field to fill
        @param j: the column of the field to fill
    */
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
        this->grid[i][j] = num;
        if (this->validator.checkBoard(this->grid))
        {
            if (fillRemaining(i, j + 1))
            {
                this->solution[i][j] = num;
                return true;
            }
        }
        this->grid[i][j] = 0;
    }
    return false;
}

void Board::removeFields()
{
    /*
        Remove 35 fields from the board to make it playable.
    */
    int count = 0;
    while (count < 35)
    {
        int cellId = rand() % 81;
        int row = cellId / 9;
        int column = cellId % 9;
        if (this->grid[row][column] != 0)
        {
            count++;
            this->grid[row][column] = 0;
        }
    }
}

// constructors / destructors
Board::Board()
{
    /*
        Constructor of the Board class.
        It initializes the board and displays the solution in the command line prompt.
    */
    this->initBoard();
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            std::cout << this->solution[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// functions
void Board::renderBoard(sf::RenderWindow &window, sf::Font font, std::vector<sf::RectangleShape> cells)
{
    /*
        Render the board on the window.
        If a field is filled, display the number in the field.
        @param window: the window to render the board on
        @param font: the font to use for the numbers
        @param cells: the vector of cells to render
    */
    for (int i = 0; i < cells.size(); i++)
    {

        window.draw(cells[i]);

        int row = i / 9;
        int column = i % 9;

        if (this->grid[row][column] != 0)
        {
            sf::Text text(std::to_string(this->grid[row][column]), font, 24);
            text.setPosition(column * 50 + 67.5, row * 50 + 160);
            text.setFillColor(sf::Color::Black);
            window.draw(text);
        }
    }
}

bool Board::updateBoard(int row, int column, int value)
{
    /*
        Update the board with the given value.
        @param row: the row of the field to update
        @param column: the column of the field to update
        @param value: the value to update the field with
        @return true if the field was updated, false otherwise
    */
    if (this->grid[row][column] == 0 && this->solution[row][column] == value)
    {
        this->grid[row][column] = value;
        return true;
    }
    return false;
}

bool Board::isFilled()
{
    /*
        Check if the board is filled.
        @return true if the board is filled, false otherwise
    */
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (this->grid[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

int Board::getFieldValue(int row, int column)
{
    /*
        Get the value of the field at the given position.
        @param row: the row of the field to get the value of
        @param column: the column of the field to get the value of
        @return the value of the field at the given position
    */
    return this->grid[row][column];
}

bool Board::numberFinished(int number)
{
    /*
        Check if the given number is finished (there's one and only one in every row, column and 3x3 square).
        @param number: the number to check
        @return true if the number is finished, false otherwise
    */
    int occurences = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (this->grid[i][j] == number)
            {
                occurences += 1;
            }
        }
    }
    if (occurences == 9)
        return true;
    else
        return false;
}
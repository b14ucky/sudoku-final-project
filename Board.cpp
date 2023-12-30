#include "Board.h"
#include <iostream>

// private functions
void Board::initBoard()
{
    this->fillDiagonal();

    this->fillRemaining(0, 3);

    this->removeFields();
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
                    this->grid[j][k] = rand() % 9 + 1;
                } while (!this->validator.checkSquare(this->grid, i, i));
                this->solution[j][k] = this->grid[j][k];
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
    if (this->grid[row][column] == 0 && this->solution[row][column] == value)
    {
        this->grid[row][column] = value;
        return true;
    }
    return false;
}

bool Board::isFilled()
{
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
    return this->grid[row][column];
}

bool Board::numberFinished(int number)
{
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
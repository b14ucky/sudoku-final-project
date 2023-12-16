#include "Board.h"

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
}

// functions
void Board::renderBoard(sf::RenderWindow &window)
{
    sf::Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            sf::RectangleShape cell(sf::Vector2f(50, 50));
            cell.setPosition(j * 50 + 50, i * 50 + 50);
            cell.setOutlineThickness(1.f);
            cell.setOutlineColor(sf::Color::Black);
            cell.setFillColor(sf::Color::White);

            window.draw(cell);

            if (this->grid[i][j] != 0)
            {
                sf::Text text(std::to_string(this->grid[i][j]), font, 20);
                text.setPosition(j * 50 + 65, i * 50 + 60);
                text.setFillColor(sf::Color::Black);
                window.draw(text);
            }
        }
    }
}
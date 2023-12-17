#pragma once

#include <SFML/Graphics.hpp>
#include "BoardValidator.h"

class Board
{
private:
    // variables
    BoardValidator validator;
    int grid[9][9]{};
    int solution[9][9]{};

    // private functions
    void initBoard();
    void fillDiagonal();
    bool fillRemaining(int i, int j);
    void removeFields();

public:
    // constructors / destructors
    Board();

    // functions
    void renderBoard(sf::RenderWindow &window, sf::Font font, std::vector<sf::RectangleShape> cells);
    bool updateBoard(int row, int column, int value);
};
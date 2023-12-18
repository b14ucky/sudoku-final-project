#pragma once

// libraries
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <ctime>
#include <iostream>
#include <vector>
#include <sstream>

#include "Board.h"

// game engine class

class Game
{
private:
    // variables
    sf::RenderWindow *window;
    sf::Event event;
    sf::VideoMode videoMode;
    Board board;

    // mouse positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // fonts
    sf::Font lightFont;
    sf::Font regularFont;

    // icons
    sf::Image icon;

    // background
    sf::Texture backgroundTexture;
    sf::Sprite background;

    // text
    sf::Text mistakesText;
    sf::Text endGameText;
    sf::Text playAgainText;
    sf::Text quitText;

    // game objects
    std::vector<sf::RectangleShape> cells;
    sf::RectangleShape cell;
    std::vector<sf::RectangleShape> gridLines;
    sf::RectangleShape gridLine;
    sf::RectangleShape endGameBackground;

    // game logic
    int selectedRow;
    int selectedColumn;
    int gridSize;
    int cellSize;
    int mistakes;

    bool mouseHeld;
    bool endGame;
    bool gameLost;

    // init functions
    void initVariables();
    void initWindow();
    void initFonts();
    void initCells();
    void initText();
    void initIcon();
    void initImages();
    void initGridLines();

public:
    // constructors / destructors
    Game();
    virtual ~Game();

    // accessors
    const bool running() const;
    const bool getEndGame() const;

    // functions
    void updateEvents();
    void updateMousePositions();
    void updateSelectedCell();
    void updateCells();
    void updateText();
    void updateEndGameMenu();
    void update();

    void render();
    void renderBackground();
    void renderGridLines();
    void renderEndGameMenu();
};
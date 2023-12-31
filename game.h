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
#include <iomanip>

#include "Board.h"
#include "Menu.h"

// game engine class

class Game
{
private:
    // variables
    sf::RenderWindow *window;
    sf::Event event;
    sf::VideoMode videoMode;
    Board board;
    Menu menu;

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
    sf::Text timerText;
    sf::Text endGameText;
    sf::Text playAgainText;
    sf::Text mainMenuText;
    sf::Text goBackText;
    sf::Text remainingNumberText;
    std::vector<sf::Text> remainingNumbers;

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

    bool madeMistake;
    bool mouseHeld;
    bool endGame;
    bool gameLost;

    sf::Clock clock;
    sf::Time elapsedTime;

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
    void updateRemainingNumbers();
    void update();

    void render();
    void renderText();
    void renderBackground();
    void renderGridLines();
    void renderEndGameMenu();
    void renderRemainingNumbers();
};
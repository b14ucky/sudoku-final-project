#pragma once

// libraries
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <ctime>
#include <iostream>

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

    // private functions
    void initVariables();
    void initWindow();

public:
    // constructors / destructors
    Game();
    virtual ~Game();

    // accessors
    const bool running() const;

    // functions
    void updateEvents();
    void update();

    void render();
};
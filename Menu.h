#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>

class Menu
{
private:
    // variables
    bool mouseHeld;

    // text
    sf::Text titleText;
    sf::Text playGameText;
    sf::Text howToPlayText;
    sf::Text creditsText;
    sf::Text quitText;
    sf::Text goBackText;
    sf::Text howToPlayInfoText;
    sf::Text creditsInfoText;

    void initVariables();
    void initText();

public:
    enum class MenuState
    {
        MainMenu,
        PlayGame,
        HowToPlay,
        Credits,
        Quit
    };

    // constructors / destructors
    Menu();

    MenuState currentState;

    void updateMainMenu(sf::Vector2f mousePosView);
    void updateHowToPlay(sf::Vector2f mousePosView);
    void updateCredits(sf::Vector2f mousePosView);

    void renderMainMenu(sf::RenderWindow &window, sf::Font &font);
    void renderHowToPlay(sf::RenderWindow &window, sf::Font &font);
    void renderCredits(sf::RenderWindow &window, sf::Font &font);
};
#include "Menu.h"

// private functions
void Menu::initVariables()
{
    /*
        Initialize the variables. Set the current menu state to MainMenu.
    */
    this->currentState = MenuState::MainMenu;

    this->mouseHeld = false;
}

void Menu::initText()
{
    /*
        Initialize the text. Set the string, size and color.
    */
    this->titleText.setCharacterSize(72);
    this->titleText.setFillColor(sf::Color(200, 200, 200));

    this->playGameText.setString("Play Game");
    this->playGameText.setCharacterSize(42);
    this->playGameText.setFillColor(sf::Color(200, 200, 200));

    this->howToPlayText.setString("How To Play");
    this->howToPlayText.setCharacterSize(42);
    this->howToPlayText.setFillColor(sf::Color(200, 200, 200));

    this->creditsText.setString("Credits");
    this->creditsText.setCharacterSize(42);
    this->creditsText.setFillColor(sf::Color(200, 200, 200));

    this->quitText.setString("Quit");
    this->quitText.setCharacterSize(42);
    this->quitText.setFillColor(sf::Color(200, 200, 200));

    this->goBackText.setString("Click to go back");
    this->goBackText.setCharacterSize(20);
    this->goBackText.setFillColor(sf::Color(200, 200, 200));

    this->howToPlayInfoText.setCharacterSize(20);
    this->howToPlayInfoText.setFillColor(sf::Color(200, 200, 200));

    this->creditsInfoText.setCharacterSize(20);
    this->creditsInfoText.setFillColor(sf::Color(200, 200, 200));
}

// constructors / destructors
Menu::Menu()
{
    /*
        Constructor of the Menu class.
        It initializes the variables and text.
    */
    this->initVariables();
    this->initText();
}

// functions
void Menu::updateMainMenu(sf::Vector2f mousePosView)
{
    /*
        Update the main menu. If the mouse is on the text, scale the text. If the mouse is pressed on the text,
        change the current menu state.
        @param mousePosView: the mouse position on the window
    */
    if (this->playGameText.getGlobalBounds().contains(mousePosView))
    {
        this->playGameText.setScale(1.1f, 1.1f);
    }
    else
    {
        this->playGameText.setScale(1.f, 1.f);
    }
    if (this->howToPlayText.getGlobalBounds().contains(mousePosView))
    {
        this->howToPlayText.setScale(1.1f, 1.1f);
    }
    else
    {
        this->howToPlayText.setScale(1.f, 1.f);
    }
    if (this->creditsText.getGlobalBounds().contains(mousePosView))
    {
        this->creditsText.setScale(1.1f, 1.1f);
    }
    else
    {
        this->creditsText.setScale(1.f, 1.f);
    }
    if (this->quitText.getGlobalBounds().contains(mousePosView))
    {
        this->quitText.setScale(1.1f, 1.1f);
    }
    else
    {
        this->quitText.setScale(1.f, 1.f);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;

            if (this->currentState == MenuState::MainMenu)
            {
                if (this->playGameText.getGlobalBounds().contains(mousePosView))
                {
                    this->currentState = MenuState::PlayGame;
                }
                else if (this->howToPlayText.getGlobalBounds().contains(mousePosView))
                {
                    this->currentState = MenuState::HowToPlay;
                }
                else if (this->creditsText.getGlobalBounds().contains(mousePosView))
                {
                    this->currentState = MenuState::Credits;
                }
                else if (this->quitText.getGlobalBounds().contains(mousePosView))
                {
                    this->currentState = MenuState::Quit;
                }
            }
        }
    }
    else
    {
        this->mouseHeld = false;
    }
}

void Menu::updateHowToPlay(sf::Vector2f mousePosView)
{
    /*
        Update the how to play menu. If the mouse is on the text, scale the text. If the mouse is pressed on the text,
        change the current menu state.
        @param mousePosView: the mouse position on the window
    */
    if (this->goBackText.getGlobalBounds().contains(mousePosView))
    {
        this->goBackText.setScale(1.1f, 1.1f);
    }
    else
    {
        this->goBackText.setScale(1.f, 1.f);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;

            if (this->currentState == MenuState::HowToPlay)
            {
                this->currentState = MenuState::MainMenu;
            }
        }
    }
    else
    {
        this->mouseHeld = false;
    }
}

void Menu::updateCredits(sf::Vector2f mousePosView)
{
    /*
        Update the credits menu. If the mouse is on the text, scale the text. If the mouse is pressed on the text,
        change the current menu state.
        @param mousePosView: the mouse position on the window
    */
    if (this->goBackText.getGlobalBounds().contains(mousePosView))
    {
        this->goBackText.setScale(1.1f, 1.1f);
    }
    else
    {
        this->goBackText.setScale(1.f, 1.f);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;

            if (this->currentState == MenuState::Credits)
            {
                this->currentState = MenuState::MainMenu;
            }
        }
    }
    else
    {
        this->mouseHeld = false;
    }
}

void Menu::renderMainMenu(sf::RenderWindow &window, sf::Font &font)
{
    /*
        Render the main menu on the window.
        @param window: the window to render the main menu on
        @param font: the font to use for the text
    */
    this->titleText.setFont(font);
    this->titleText.setString("Sudoku");
    this->titleText.setPosition(275 - this->titleText.getGlobalBounds().width / 2, 100);

    playGameText.setFont(font);
    this->playGameText.setPosition(275 - this->playGameText.getGlobalBounds().width / 2, 275);

    howToPlayText.setFont(font);
    this->howToPlayText.setPosition(275 - this->howToPlayText.getGlobalBounds().width / 2, 350);

    creditsText.setFont(font);
    this->creditsText.setPosition(275 - this->creditsText.getGlobalBounds().width / 2, 425);

    quitText.setFont(font);
    this->quitText.setPosition(275 - this->quitText.getGlobalBounds().width / 2, 500);

    window.draw(this->titleText);
    window.draw(this->playGameText);
    window.draw(this->howToPlayText);
    window.draw(this->creditsText);
    window.draw(this->quitText);
}

void Menu::renderHowToPlay(sf::RenderWindow &window, sf::Font &font)
{
    /*
        Render the how to play menu on the window.
        @param window: the window to render the how to play menu on
        @param font: the font to use for the text
    */
    this->titleText.setPosition(275 - this->titleText.getGlobalBounds().width / 2, 100);
    this->titleText.setString("How To Play");
    this->titleText.setFont(font);

    this->howToPlayInfoText.setPosition(275 - this->howToPlayInfoText.getGlobalBounds().width / 2, 250);
    this->howToPlayInfoText.setFont(font);

    std::stringstream howToPlayInfo;
    howToPlayInfo << "1. Each row, column and 3x3 box\nmust contain all numbers from 1 to 9." << std::endl
                  << "2. Each row, column and 3x3 box\nmust contain unique numbers." << std::endl
                  << "3. You can't update non empty field." << std::endl
                  << "4. You can't update field with invalid value." << std::endl
                  << "5. There's always only one solution." << std::endl
                  << "6. You lose if you make 3 mistakes\nor if your game takes longer than 1 hour." << std::endl;
    this->howToPlayInfoText.setString(howToPlayInfo.str());

    this->goBackText.setFont(font);
    this->goBackText.setPosition(275 - this->goBackText.getGlobalBounds().width / 2, 650);

    window.draw(this->titleText);
    window.draw(this->howToPlayInfoText);
    window.draw(this->goBackText);
}

void Menu::renderCredits(sf::RenderWindow &window, sf::Font &font)
{
    /*
        Render the credits menu on the window.
        @param window: the window to render the credits menu on
        @param font: the font to use for the text
    */
    this->titleText.setPosition(275 - this->titleText.getGlobalBounds().width / 2, 100);
    this->titleText.setString("Credits");
    this->titleText.setFont(font);

    std::stringstream creditsInfo;
    creditsInfo << "Credits:" << std::endl
                << "Author: Dominik Meisner" << std::endl
                << "GitHub: https://github.com/b14ucky/sudoku-final-project" << std::endl
                << "Version: 1.1.2";

    this->creditsInfoText.setString(creditsInfo.str());
    this->creditsInfoText.setPosition(275 - this->creditsInfoText.getGlobalBounds().width / 2, 250);
    this->creditsInfoText.setFont(font);

    this->goBackText.setFont(font);
    this->goBackText.setPosition(275 - this->goBackText.getGlobalBounds().width / 2, 650);

    window.draw(this->titleText);
    window.draw(this->creditsInfoText);
    window.draw(this->goBackText);
}
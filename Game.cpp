#include "Game.h"

// init functions
void Game::initVariables()
{
    /*
        Initialize all variables that will be used in the game and set their default values
    */
    this->window = nullptr;

    this->selectedRow = -1;
    this->selectedColumn = -1;
    this->gridSize = 9;
    this->cellSize = 50;
    this->mistakes = 0;

    this->madeMistake = false;
    this->mouseHeld = false;
    this->endGame = false;
    this->gameLost = false;
}

void Game::initWindow()
{
    /*
        Initialize the window that will be used in the game, set its size and title
    */
    this->videoMode.height = 800;
    this->videoMode.width = 550;
    this->window = new sf::RenderWindow(this->videoMode, "Sudoku", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
    /*
        Load fonts from the assets folder and display an error message if the font could not be loaded
    */
    if (!this->lightFont.loadFromFile("./assets/fonts/Cairo-ExtraLight.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONTS::Failed to load light font!" << std::endl;
    }
    if (!this->regularFont.loadFromFile("./assets/fonts/Cairo-Regular.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONTS::Failed to load medium font!" << std::endl;
    }
}

void Game::initCells()
{
    /*
        Initialize the grid of cells that will be used in the game, set their size, position,
        outline thickness, fill color and outline color and add them to the vector of cells
    */
    for (int i = 0; i < this->gridSize * this->gridSize; i++)
    {
        int row = i / this->gridSize;
        int column = i % this->gridSize;

        this->cell.setPosition((i % this->gridSize) * this->cellSize + 50, (i / this->gridSize) * this->cellSize + 150);
        this->cell.setSize(sf::Vector2f(cellSize, cellSize));
        this->cell.setOutlineThickness(1.f);
        this->cell.setFillColor(sf::Color::White);
        this->cell.setOutlineColor(sf::Color::Black);
        this->cells.push_back(cell);
    }
}

void Game::initText()
{
    /*
        Initialize the text that will be used in the game, set their font, position, character size,
        fill color and the default string that will be displayed on the screen
    */
    this->mistakesText.setFont(this->lightFont);
    this->mistakesText.setPosition(50, 100);
    this->mistakesText.setCharacterSize(28);
    this->mistakesText.setFillColor(sf::Color(200, 200, 200));
    this->mistakesText.setString("NONE");

    this->timerText.setFont(this->lightFont);
    this->timerText.setPosition(365, 100);
    this->timerText.setCharacterSize(28);
    this->timerText.setFillColor(sf::Color(200, 200, 200));
    this->timerText.setString("NONE");
    this->timerText.setPosition(365, 100);

    this->endGameText.setFont(this->lightFont);
    this->endGameText.setCharacterSize(48);
    this->endGameText.setFillColor(sf::Color::Black);

    this->playAgainText.setFont(this->regularFont);
    this->playAgainText.setCharacterSize(28);
    this->playAgainText.setString("Play again");
    this->playAgainText.setOrigin(playAgainText.getLocalBounds().width / 2.f, playAgainText.getLocalBounds().height / 2.f);
    this->playAgainText.setPosition(275, 350);
    this->playAgainText.setFillColor(sf::Color::Black);

    this->mainMenuText.setFont(this->regularFont);
    this->mainMenuText.setCharacterSize(28);
    this->mainMenuText.setString("Main menu");
    this->mainMenuText.setOrigin(mainMenuText.getLocalBounds().width / 2.f, mainMenuText.getLocalBounds().height / 2.f);
    this->mainMenuText.setPosition(275, 450);
    this->mainMenuText.setFillColor(sf::Color::Black);

    this->goBackText.setFont(this->lightFont);
    this->goBackText.setCharacterSize(28);
    this->goBackText.setString("Click here to go back to main menu");
    this->goBackText.setOrigin(goBackText.getLocalBounds().width / 2.f, goBackText.getLocalBounds().height / 2.f);
    this->goBackText.setPosition(275, 750);
    this->goBackText.setFillColor(sf::Color(200, 200, 200));

    this->remainingNumberText.setFont(this->regularFont);
    this->remainingNumberText.setCharacterSize(32);
    this->remainingNumberText.setFillColor(sf::Color(200, 200, 200));
    this->remainingNumberText.setOutlineColor(sf::Color::Black);
    this->remainingNumberText.setOutlineThickness(1.f);

    for (int i = 0; i < 9; i++)
    {
        this->remainingNumberText.setString(std::to_string(i + 1));
        this->remainingNumberText.setPosition(50 + i * 50 + 17.5, 650);
        this->remainingNumbers.push_back(remainingNumberText);
    }
}

void Game::initIcon()
{
    /*
        Load the icon from the assets folder and display an error message if the icon could not be loaded
    */
    if (!this->icon.loadFromFile("./assets/icons/icon.png"))
    {
        std::cout << "ERROR::GAME::INITICON::Failed to load icon!" << std::endl;
    }
    this->window->setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());
}

void Game::initImages()
{
    /*
        Load the background image from the assets folder and display an error message if the image could not be loaded
    */
    if (!this->backgroundTexture.loadFromFile("./assets/images/background.png"))
    {
        std::cout << "ERROR::GAME::INITIMAGES::Failed to load background!" << std::endl;
    }
    this->background.setTexture(this->backgroundTexture);
}

void Game::initGridLines()
{
    /*
        Initialize the grid lines that will be used in the game, set their size, position,
        fill color and add them to the vector of grid lines
    */
    this->gridLine.setFillColor(sf::Color::Black);
    this->gridLine.setSize(sf::Vector2f(2.f, 450.f));
    this->gridLine.setPosition(200, 150);
    this->gridLines.push_back(gridLine);
    this->gridLine.setPosition(350, 150);
    this->gridLines.push_back(gridLine);
    this->gridLine.setSize(sf::Vector2f(450.f, 2.f));
    this->gridLine.setPosition(50, 300);
    this->gridLines.push_back(gridLine);
    this->gridLine.setPosition(50, 450);
    this->gridLines.push_back(gridLine);
}

// constructors / destructors
Game::Game()
{
    /*
        Call all init functions to initialize the game
    */
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initCells();
    this->initText();
    this->initIcon();
    this->initImages();
    this->initGridLines();
}

Game::~Game()
{
    delete this->window;
}

// accessors
const bool Game::running() const
{
    // returns the game window status
    return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    // returns the end game status
    return this->endGame;
}

// update functions
void Game::updateEvents()
{
    /*
        Poll all events that happen in the game window and update the game accordingly
    */
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            /*
                This event is responsible for closing the game window
            */
            this->window->close();
            break;
        case sf::Event::TextEntered:
            /*
                This event is responsible for updating the cells when the user enters a number
            */
            if (this->menu.currentState != Menu::MenuState::PlayGame)
                break;
            if (this->selectedRow != -1 && this->selectedColumn != -1 && this->event.text.unicode >= '1' && this->event.text.unicode <= '9')
            {
                int value = this->event.text.unicode - '0';
                if (!this->board.updateBoard(this->selectedRow, this->selectedColumn, value))
                {
                    this->madeMistake = true;
                    this->mistakes += 1;
                }
                else
                {
                    this->madeMistake = false;
                }
            }
            if (this->board.isFilled())
            {
                this->endGame = true;
            }
            break;
        case sf::Event::KeyPressed:
            /*
                This event is responsible for updating the selected cell when the user presses the arrow keys
            */
            if (this->menu.currentState != Menu::MenuState::PlayGame)
                break;
            if (this->madeMistake)
                this->madeMistake = false;
            if (this->event.key.code == sf::Keyboard::Up)
            {
                if (this->selectedRow == -1 && this->selectedColumn == -1)
                {
                    this->selectedRow = 0;
                    this->selectedColumn = 0;
                }
                else
                {
                    this->selectedRow -= 1;
                    if (this->selectedRow < 0 || this->selectedRow > 8)
                    {
                        this->selectedRow = -1;
                        this->selectedColumn = -1;
                    }
                }
            }
            if (this->event.key.code == sf::Keyboard::Down)
            {
                if (this->selectedRow == -1 && this->selectedColumn == -1)
                {
                    this->selectedRow = 0;
                    this->selectedColumn = 0;
                }
                else
                {
                    this->selectedRow += 1;
                    if (this->selectedRow < 0 || this->selectedRow > 8)
                    {
                        this->selectedRow = -1;
                        this->selectedColumn = -1;
                    }
                }
            }
            if (this->event.key.code == sf::Keyboard::Left)
            {
                if (this->selectedRow == -1 && this->selectedColumn == -1)
                {
                    this->selectedRow = 0;
                    this->selectedColumn = 0;
                }
                else
                {
                    this->selectedColumn -= 1;
                    if (this->selectedColumn < 0 || this->selectedColumn > 8)
                    {
                        this->selectedRow = -1;
                        this->selectedColumn = -1;
                    }
                }
            }
            if (this->event.key.code == sf::Keyboard::Right)
            {
                if (this->selectedRow == -1 && this->selectedColumn == -1)
                {
                    this->selectedRow = 0;
                    this->selectedColumn = 0;
                }
                else
                {
                    this->selectedColumn += 1;
                    if (this->selectedColumn < 0 || this->selectedColumn > 8)
                    {
                        this->selectedRow = -1;
                        this->selectedColumn = -1;
                    }
                }
            }
            break;
        }
    }
}

void Game::updateMousePositions()
{
    /*
        Update the mouse position in the game window and save it in the mousePosWindow and mousePosView variables
    */
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateSelectedCell()
{
    /*
        Update the selected cell in the game window and save it in the selectedRow and selectedColumn variables,
        which are then used to update the cells in the game window
    */
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            if (this->madeMistake)
            {
                this->madeMistake = false;
            }
            this->mouseHeld = true;

            for (int i = 0; i < gridSize * gridSize; i++)
            {
                if (this->cells[i].getGlobalBounds().contains(this->mousePosView))
                {
                    this->selectedRow = i / this->gridSize;
                    this->selectedColumn = i % this->gridSize;
                    break;
                }
                else
                {
                    this->selectedRow = -1;
                    this->selectedColumn = -1;
                }
            }
        }
    }
    else
    {
        this->mouseHeld = false;
    }
}

void Game::updateCells()
{
    /*
        Update the cells in the game window and change their fill color depending on the selected cell,
        the cells that have the same value as the selected cell and the cells in the same row or column
        as the selected cell and save the changes in the cells vector
    */
    for (int i = 0; i < this->gridSize; i++)
    {
        for (int j = 0; j < this->gridSize; j++)
        {
            int currentCell = i * this->gridSize + j;
            if (i == this->selectedRow && j == this->selectedColumn)
            {
                this->cells[currentCell].setFillColor(sf::Color(150, 150, 150, 128));
            }
            else if (this->board.getFieldValue(i, j) != 0 && this->board.getFieldValue(i, j) == this->board.getFieldValue(this->selectedRow, this->selectedColumn))
            {
                this->cells[currentCell].setFillColor(sf::Color(200, 200, 200, 128));
            }
            else if (i == this->selectedRow)
            {
                this->cells[currentCell].setFillColor(sf::Color(225, 225, 225, 128));
            }
            else if (j == this->selectedColumn)
            {
                this->cells[currentCell].setFillColor(sf::Color(225, 225, 225, 128));
            }
            else
            {
                this->cells[currentCell].setFillColor(sf::Color(255, 255, 255, 128));
            }

            if (this->madeMistake)
            {
                int mistakenCell = this->selectedRow * this->gridSize + this->selectedColumn;
                this->cells[mistakenCell].setFillColor(sf::Color(255, 51, 51, 128));
            }
        }
    }
}

void Game::updateText()
{
    /*
        Update the text in the game window and change their string depending on the number of mistakes
        and the time elapsed since the game started
    */
    std::stringstream mistakesString;
    mistakesString << "Mistakes: " << this->mistakes;
    this->mistakesText.setString(mistakesString.str());

    this->elapsedTime = this->clock.getElapsedTime();
    int totalSeconds = static_cast<int>(this->elapsedTime.asSeconds());
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    std::stringstream timeString;
    timeString << "Time: " << std::setfill('0') << std::setw(2) << minutes << ":" << std::setfill('0') << std::setw(2) << seconds;
    this->timerText.setString(timeString.str());

    if (this->goBackText.getGlobalBounds().contains(this->mousePosView))
    {
        this->goBackText.setScale(1.1f, 1.1f);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->mouseHeld = true;
            this->endGame = false;
            this->gameLost = false;
            this->mistakes = 0;
            this->board = Board();
            this->menu.currentState = Menu::MenuState::MainMenu;
        }
    }
    else
    {
        this->goBackText.setScale(1.f, 1.f);
    }
}

void Game::updateEndGameMenu()
{
    /*
        Update the end game menu in the game window and change the string of the end game text depending
        on the game status and the string of the play again and main menu text depending on the mouse position
    */
    if (this->playAgainText.getGlobalBounds().contains(this->mousePosView))
    {
        this->playAgainText.setFillColor(sf::Color(5, 5, 5));
        this->playAgainText.setScale(1.1f, 1.1f);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->endGame = false;
            this->gameLost = false;
            this->mistakes = 0;
            this->board = Board();
            this->clock.restart();
        }
    }
    else
    {
        this->playAgainText.setFillColor(sf::Color::Black);
        this->playAgainText.setScale(1.f, 1.f);
    }
    if (this->mainMenuText.getGlobalBounds().contains(this->mousePosView))
    {
        this->mainMenuText.setFillColor(sf::Color(5, 5, 5));
        this->mainMenuText.setScale(1.1f, 1.1f);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->endGame = false;
            this->gameLost = false;
            this->mistakes = 0;
            this->board = Board();
            this->clock.restart();
            this->menu.currentState = Menu::MenuState::MainMenu;
        }
    }
    else
    {
        this->mainMenuText.setFillColor(sf::Color::Black);
        this->mainMenuText.setScale(1.f, 1.f);
    }
}

void Game::updateRemainingNumbers()
{
    /*
        Update the remaining numbers in the game window and change their string depending on the numbers
        that have been already used in the game
    */
    for (size_t i = 0; i < 9; i++)
    {
        if (this->board.numberFinished(i + 1))
        {
            this->remainingNumbers[i].setString(" ");
        }
        else
        {
            this->remainingNumbers[i].setString(std::to_string(i + 1));
        }
    }
}

// render functions
void Game::renderText()
{
    /*
        Draw the text in the game window
    */
    this->window->draw(this->mistakesText);
    this->window->draw(this->timerText);
    this->window->draw(this->goBackText);
}

void Game::renderBackground()
{
    /*
        Draw the background in the game window
    */
    this->window->draw(this->background);
}

void Game::renderGridLines()
{
    /*
        Draw the grid lines in the game window
    */
    for (auto &gridLine : this->gridLines)
    {
        this->window->draw(gridLine);
    }
}

void Game::renderEndGameMenu()
{
    /*
        Draw the end game menu in the game window
    */

    // set end game background
    this->endGameBackground.setSize(sf::Vector2f(275.f, 400.f));
    this->endGameBackground.setPosition(137.5, 175);
    this->endGameBackground.setFillColor(sf::Color(255, 255, 255, 225));

    // set end game text position
    this->endGameText.setPosition((this->window->getSize().x - endGameText.getLocalBounds().width) / 2.f, 200);

    // set end game text string
    if (this->gameLost)
        this->endGameText.setString("You lost!");
    else
        this->endGameText.setString("You won!");

    // render end game menu
    this->window->draw(this->endGameBackground);
    this->window->draw(this->endGameText);
    this->window->draw(this->playAgainText);
    this->window->draw(this->mainMenuText);
}

void Game::renderRemainingNumbers()
{
    /*
        Draw the remaining numbers in the game window
    */
    for (auto &remainingNumber : this->remainingNumbers)
    {
        this->window->draw(remainingNumber);
    }
}

// main functions

void Game::update()
{
    /*
        Update the game window
    */

    this->updateEvents();

    this->updateMousePositions();

    switch (this->menu.currentState)
    {
    case Menu::MenuState::MainMenu:
        this->clock.restart();
        this->menu.updateMainMenu(this->mousePosView);
        break;
    case Menu::MenuState::PlayGame:
        if (!this->endGame)
        {
            this->updateSelectedCell();

            this->updateCells();

            this->updateRemainingNumbers();

            this->updateText();
        }

        if (this->mistakes >= 3 || this->elapsedTime.asSeconds() > 3599)
        {
            this->endGame = true;
            this->gameLost = true;
        }

        if (this->getEndGame())
        {
            this->updateEndGameMenu();
        }
        break;
    case Menu::MenuState::HowToPlay:
        this->menu.updateHowToPlay(this->mousePosView);
        break;
    case Menu::MenuState::Credits:
        this->menu.updateCredits(this->mousePosView);
        break;
    case Menu::MenuState::Quit:
        this->window->close();
        break;
    }
}

void Game::render()
{
    /*
        Render the game window
    */

    // clear old frame
    this->window->clear(sf::Color::White);

    // render background
    this->renderBackground();

    // render items
    switch (this->menu.currentState)
    {
    case Menu::MenuState::MainMenu:
        this->menu.renderMainMenu(*this->window, this->regularFont);
        break;
    case Menu::MenuState::PlayGame:
        this->board.renderBoard(*this->window, this->regularFont, this->cells);

        this->renderGridLines();

        this->renderText();

        this->renderRemainingNumbers();

        if (this->getEndGame())
        {

            this->renderEndGameMenu();
        }
        break;
    case Menu::MenuState::HowToPlay:
        this->menu.renderHowToPlay(*this->window, this->regularFont);
        break;
    case Menu::MenuState::Credits:
        this->menu.renderCredits(*this->window, this->regularFont);
        break;
    }

    // display frame in window
    this->window->display();
}
#include "Game.h"

// init functions
void Game::initVariables()
{
    this->window = nullptr;

    this->selectedRow = -1;
    this->selectedColumn = -1;
    this->gridSize = 9;
    this->cellSize = 50;
    this->mistakes = 0;

    this->mouseHeld = false;
    this->endGame = false;
    this->gameLost = false;
}

void Game::initWindow()
{
    this->videoMode.height = 800;
    this->videoMode.width = 550;
    this->window = new sf::RenderWindow(this->videoMode, "Sudoku", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
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

    this->goBackText.setFont(this->regularFont);
    this->goBackText.setCharacterSize(28);
    this->goBackText.setString("Click here to go back to main menu");
    this->goBackText.setOrigin(goBackText.getLocalBounds().width / 2.f, goBackText.getLocalBounds().height / 2.f);
    this->goBackText.setPosition(275, 750);
    this->goBackText.setFillColor(sf::Color(200, 200, 200));
}

void Game::initIcon()
{
    if (!this->icon.loadFromFile("./assets/icons/icon.png"))
    {
        std::cout << "ERROR::GAME::INITICON::Failed to load icon!" << std::endl;
    }
    this->window->setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());
}

void Game::initImages()
{
    if (!this->backgroundTexture.loadFromFile("./assets/images/background.png"))
    {
        std::cout << "ERROR::GAME::INITIMAGES::Failed to load background!" << std::endl;
    }
    this->background.setTexture(this->backgroundTexture);
}

void Game::initGridLines()
{
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
    return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return this->endGame;
}

// update functions
void Game::updateEvents()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::TextEntered:
            if (this->selectedRow != -1 && this->selectedColumn != -1 && event.text.unicode >= '1' && event.text.unicode <= '9')
            {
                int value = event.text.unicode - '0';
                if (!this->board.updateBoard(this->selectedRow, this->selectedColumn, value))
                    this->mistakes += 1;
            }
            if (this->board.isFilled())
            {
                this->endGame = true;
            }
            break;
        }
    }
}

void Game::updateMousePositions()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateSelectedCell()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
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
    for (int i = 0; i < gridSize * gridSize; i++)
    {
        int selectedCell = this->selectedRow * this->gridSize + this->selectedColumn;
        if (i == selectedCell)
        {
            this->cells[i].setFillColor(sf::Color(200, 200, 200, 128));
        }
        else
        {
            this->cells[i].setFillColor(sf::Color(255, 255, 255, 128));
        }
    }
}

void Game::updateText()
{
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

// render functions
void Game::renderText()
{
    this->window->draw(this->mistakesText);
    this->window->draw(this->timerText);
    this->window->draw(this->goBackText);
}

void Game::renderBackground()
{
    this->window->draw(this->background);
}

void Game::renderGridLines()
{
    for (auto &gridLine : this->gridLines)
    {
        this->window->draw(gridLine);
    }
}

void Game::renderEndGameMenu()
{
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

// main functions

void Game::update()
{
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
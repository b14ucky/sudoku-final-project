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
}

// render functions

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

// main functions

void Game::update()
{
    this->updateEvents();

    if (!this->endGame)
    {
        this->updateMousePositions();

        this->updateSelectedCell();

        this->updateCells();

        this->updateText();
    }

    if (this->mistakes >= 3)
    {
        this->endGame = true;
    }
}

void Game::render()
{
    // clear old frame
    this->window->clear(sf::Color::White);

    // render background
    this->renderBackground();

    // render items
    this->board.renderBoard(*this->window, this->regularFont, this->cells);

    this->renderGridLines();

    this->window->draw(this->mistakesText);

    // display frame in window
    this->window->display();
}
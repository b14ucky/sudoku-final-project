#include "Game.h"

// private functions
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
    if (!this->defaultFont.loadFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << std::endl;
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
    this->mistakesText.setFont(this->defaultFont);
    this->mistakesText.setPosition(50, 100);
    this->mistakesText.setCharacterSize(24);
    this->mistakesText.setFillColor(sf::Color::Black);
    this->mistakesText.setString("NONE");
}

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initCells();
    this->initText();
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

// functions
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
            std::cout << "Mistakes: " << this->mistakes << std::endl;
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
            this->cells[i].setFillColor(sf::Color(200, 200, 200));
        }
        else
        {
            this->cells[i].setFillColor(sf::Color::White);
        }
    }
}

void Game::updateText()
{
    std::stringstream mistakesString;
    mistakesString << "Mistakes: " << this->mistakes;
    this->mistakesText.setString(mistakesString.str());
}

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

    // render items
    this->board.renderBoard(*this->window, this->defaultFont, this->cells);

    this->window->draw(this->mistakesText);

    // display frame in window
    this->window->display();
}
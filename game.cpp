#include <iostream>
#include <cctype>

#include "game.h"
#include "board.h"
#include "tests.h"

using namespace std;

void Game::runGame()
{
    displayMenu();
}

void Game::displayRules()
{
    cout << "Rules:" << endl;
    cout << "1. Each row, column and 3x3 box must contain all numbers from 1 to 9" << endl;
    cout << "2. Each row, column and 3x3 box must contain unique numbers" << endl;
    cout << "3. You can't update non empty field" << endl;
    cout << "4. You can't update field with invalid value" << endl;
    cout << "5. You can't update field with invalid row or column" << endl;
    cout << endl;
    system("pause");
    system("cls");
    displayMenu();
}

void Game::displayCredits()
{
    cout << "Credits:" << endl;
    cout << "Author: Dominik Meisner" << endl;
    cout << "GitHub: https://github.com/b14ucky/sudoku-final-project" << endl;
    cout << "Version: 1.0" << endl;
    cout << endl;
    system("pause");
    system("cls");
    displayMenu();
}

void Game::displayMenu()
{
    bool exitMenu = false;

    while (!exitMenu)
    {
        cout << "Welcome to Sudoku!" << endl;
        cout << "1. Play Game" << endl;
        cout << "2. Rules" << endl;
        cout << "3. Credits" << endl;
        cout << "4. Exit" << endl;
        cout << "5. Run tests" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            exitMenu = true;
            playGame();
            break;
        case 2:
            system("cls");
            displayRules();
            break;
        case 3:
            system("cls");
            displayCredits();
            break;
        case 4:
        {
            char exitChoice{};
            cout << "Are you sure? [Y/N]: ";
            cin >> exitChoice;
            switch (toupper(exitChoice))
            {
            case 'Y':
                exitMenu = true;
                break;
            case 'N':
                system("cls");
                displayMenu();
                break;
            default:
                cout << "Invalid choice" << endl;
                system("pause");
                system("cls");
                break;
            }
            exitMenu = true;
            break;
        }
        case 5:
        {
            system("cls");
            Tests tests;
            tests.runAllTests();
            system("pause");
            system("cls");
            break;
        }
        default:
            cout << "Invalid choice" << endl;
            system("pause");
            system("cls");
            break;
        }
    }
}

int Game::displayFieldSelectionMenu(Board &board)
{
    cout << endl
         << "Choose field to update: " << endl;
    cout << "Row[1-9]: ";
    int row{};
    cin >> row;
    cout << "Column[A-I]: ";
    char column{};
    cin >> column;
    cout << "Value[1-9]: ";
    int value{};
    cin >> value;
    return board.updateBoard(row, column, value);
}

void Game::displayEndGameMenu(bool gameWon, int mistakes)
{
    if (gameWon)
    {
        bool exitMenu = false;

        while (!exitMenu)
        {
            cout << "Congratulations! You won!" << endl;
            cout << "You've made: " << mistakes << " mistakes" << endl;
            cout << endl
                 << "Would you like to play again? [Y/N]: ";
            char choice{};
            cin >> choice;
            switch (toupper(choice))
            {
            case 'Y':
                system("cls");
                exitMenu = true;
                displayMenu();
                break;
            case 'N':
                cout << "Thanks for playing!" << endl;
                system("pause");
                exitMenu = true;
                break;
            default:
                cout << "Invalid choice" << endl;
                system("pause");
                system("cls");
                break;
            }
        }
    }
    else
    {
        bool exitMenu = false;

        while (!exitMenu)
        {
            cout << "You lost!" << endl;
            cout << "You've made: " << mistakes << " mistakes" << endl;
            cout << endl
                 << "Would you like to play again? [Y/N]: ";
            char choice{};
            cin >> choice;
            switch (toupper(choice))
            {
            case 'Y':
                system("cls");
                exitMenu = true;
                displayMenu();
                break;
            case 'N':
                cout << "Thanks for playing!" << endl;
                system("pause");
                exitMenu = true;
                break;
            default:
                cout << "Invalid choice" << endl;
                system("pause");
                system("cls");
                break;
            }
        }
    }
}

void Game::playGame()
{
    system("cls");
    Board board;
    board.generateBoard();

    int mistakes = 0;
    while (true)
    {
        if (board.checkIfBoardIsFilled())
        {
            displayEndGameMenu(true, mistakes);
            break;
        }
        if (mistakes == 10)
        {
            displayEndGameMenu(false, mistakes);
            break;
        }
        cout << "Mistakes: " << mistakes << "/10" << endl;
        board.printBoard();
        switch (displayFieldSelectionMenu(board))
        {
        case -2: // Invalid row or column
            cout << "Invalid input" << endl;
            system("pause");
            system("cls");
            break;
        case -1: // Can't update existing field
            cout << "Can't update non empty field" << endl;
            system("pause");
            system("cls");
            break;
        case 0: // Incorrect
            mistakes++;
            system("cls");
            break;
        case 1: // Correct
            system("cls");
            break;
        }
    }
}
#pragma once

#include "board.h"

class Game
{
public:
    void runGame();
    void displayMenu();
    void playGame();
    int displayFieldSelectionMenu(Board &board);
    void displayEndGameMenu(bool gameWon, int mistakes);
    void displayRules();
    void displayCredits();
};
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#include "board.h"
#include "validate.h"
#include "game.h"

int main()
{
    srand(time(NULL));
    Game game;
    game.runGame();
    return 0;
}
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#include "board.h"
#include "validate.h"
#include "game.h"

using namespace std;

int main()
{
    srand(time(NULL));
    Game game;
    game.runGame();
}
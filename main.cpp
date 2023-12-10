#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#include "board.h"
#include "validate.h"

using namespace std;

int main()
{
    srand(time(NULL));
    Board board;
    board.printBoard();
    system("pause");
}
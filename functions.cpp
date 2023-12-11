#include <cctype>

#include "functions.h"

int Functions::columnSymbolToColumnNumber(char column)
{
    column = toupper(column);
    column = (int)column - 65;
    if (column < 0 || column > 8)
        return -1;
    return column;
}
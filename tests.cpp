#include "tests.h"
#include "testCase.h"

#include "validate.h"
#include "board.h"

void Tests::runAllTests()
{
    int testsPassed = 0;
    int testsFailed = 0;
    cout << "Running all tests..." << endl;

    // Add tests here
    testCheckBoard(testsPassed, testsFailed);
    testSolvedBoardEqualsBoard(testsPassed, testsFailed);
    testRemoveFields(testsPassed, testsFailed);
    testUpdateBoard(testsPassed, testsFailed);
    testCheckIfBoardIsFilled(testsPassed, testsFailed);

    cout << "Ran " << testsPassed + testsFailed << " tests. " << endl
         << testsPassed << "/" << testsPassed + testsFailed << " passed." << endl;
}

void Tests::testCheckBoard(int &testsPassed, int &testsFailed)
{
    TestCase testCase;
    Validate validate;
    int testBoard[9][9]{
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}};

    bool passed = testCase.assertIs(validate.checkBoard(testBoard), true, "testCheckBoard()");
    if (passed)
        testsPassed++;
    else
        testsFailed++;
}

void Tests::testSolvedBoardEqualsBoard(int &testsPassed, int &testsFailed)
{
    TestCase testCase;
    Board board;

    board.fillDiagonal();
    board.fillRemaining(0, 3);

    bool passed = true;
    bool result = true;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board.board[i][j] != board.solvedBoard[i][j])
            {
                result = false;
                goto stop;
            }
        }
    }

    passed = testCase.assertIs(result, true, "testSolvedBoardEqualsBoard()");

stop:
{
    passed = testCase.assertIs(result, true, "testSolvedBoardEqualsBoard()");
}

    if (passed)
        testsPassed++;
    else
        testsFailed++;
}

void Tests::testRemoveFields(int &testsPassed, int &testsFailed)
{
    TestCase testCase;
    Board board;

    board.generateBoard();

    bool result = true;
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board.board[i][j] == 0)
            {
                count++;
            }
        }
    }
    bool passed = testCase.assertEqualsInt(count, 35, "testRemoveFields()");
    if (passed)
        testsPassed++;
    else
        testsFailed++;
}

void Tests::testUpdateBoard(int &testsPassed, int &testsFailed)
{
    TestCase testCase;
    Board board;

    board.generateBoard();

    int row{};
    char column{};
    int testValue{};

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board.board[i][j] == 0)
            {
                row = i + 1;
                column = (char)(j + 65);
                testValue = board.solvedBoard[i][j];
                goto stop;
            }
        }
    }

stop:
{
    int testIncorrectValue{};
    if (testValue > 1)
    {
        testIncorrectValue = testValue - 1;
    }
    else
    {
        testIncorrectValue = testValue + 1;
    }
    bool passed = testCase.assertEqualsInt(board.updateBoard(row, column, testIncorrectValue), 0, "testUpdateBoard() check if correct value was returned when trying to update field with incorrect value");
    if (passed)
        testsPassed++;
    else
        testsFailed++;
    passed = testCase.assertEqualsInt(board.updateBoard(row, column, testValue), 1, "testUpdateBoard() check if correct value was returned when updating field");
    if (passed)
        testsPassed++;
    else
        testsFailed++;
    passed = testCase.assertEqualsInt(board.board[row - 1][(int)column - 65], testValue, "testUpdateBoard() check if board was updated correctly");
    if (passed)
        testsPassed++;
    else
        testsFailed++;
    // we know that the field is already updated so we try to update it again
    passed = testCase.assertEqualsInt(board.updateBoard(row, column, testValue), -1, "testUpdateBoard() check if correct value was returned when trying to update already filled field");
    if (passed)
        testsPassed++;
    else
        testsFailed++;
    passed = testCase.assertEqualsInt(board.updateBoard(-1, column, 0), -2, "testUpdateBoard() check if correct value was returned when trying to update field with invalid row value");
    if (passed)
        testsPassed++;
    else
        testsFailed++;
}
}

void Tests::testCheckIfBoardIsFilled(int &testsPassed, int &testsFailed)
{
    TestCase testCase;
    Board board;

    board.generateBoard();

    bool passed = testCase.assertIs(board.checkIfBoardIsFilled(), false, "testCheckIfBoardIsFilled() check if board is filled when it's not");
    if (passed)
        testsPassed++;
    else
        testsFailed++;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board.board[i][j] = board.solvedBoard[i][j];
        }
    }

    passed = testCase.assertIs(board.checkIfBoardIsFilled(), true, "testCheckIfBoardIsFilled() check if board is filled when it is");
    if (passed)
        testsPassed++;
    else
        testsFailed++;
}
#pragma once

class Tests
{
public:
    void runAllTests();
    void testCheckBoard(int &testsPassed, int &testsFailed);
    void testSolvedBoardEqualsBoard(int &testsPassed, int &testsFailed);
    void testRemoveFields(int &testsPassed, int &testsFailed);
    void testUpdateBoard(int &testsPassed, int &testsFailed);
    void testCheckIfBoardIsFilled(int &testsPassed, int &testsFailed);
};
#include <iostream>

#include "testCase.h"

using namespace std;

bool TestCase::assertIs(bool actual, bool expected, string testName)
{
    if (expected == actual)
    {
        cout << "Test \"" << testName << "\" passed." << endl;
        return true;
    }
    else
    {
        cout << "Test \"" << testName << "\" failed. " << actual << " != " << expected << endl;
        return false;
    }
}

bool TestCase::assertEqualsInt(int actual, int expected, string testName)
{
    if (expected == actual)
    {
        cout << "Test \"" << testName << "\" passed." << endl;
        return true;
    }
    else
    {
        cout << "Test \"" << testName << "\" failed. " << actual << " should be " << expected << endl;
        return false;
    }
}
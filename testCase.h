#pragma once

#include <iostream>

using namespace std;

class TestCase
{
public:
    bool assertIs(bool acutal, bool expected, string testName);
    bool assertEqualsInt(int actual, int expected, string testName);
};
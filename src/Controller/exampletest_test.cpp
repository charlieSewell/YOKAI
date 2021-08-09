#include "CppUTest/TestHarness.h"

TEST_GROUP(FirstTestGroup)
{
};

TEST(FirstTestGroup, FirstTest)
{
	FAIL("Fail Me!");
}

TEST(FirstTestGroup, SecondTest)
{
	STRCMP_EQUAL("Hello", "World");
}
#include <CppUTest/CommandLineTestRunner.h>
#include <sstream>
#include <fstream>
int main(int ac, char** av)
{
	return CommandLineTestRunner::RunAllTests(ac, av);
}
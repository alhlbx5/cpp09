#include "PmergeMe.hpp"
#include <cstdlib>
#include <ctime>

void	testWithArgs(int argc, char **argv)
{
	PmergeMe	sorter;

	sorter.processArguments(argc, argv);
}

void	testWithRandomData(int size)
{
	PmergeMe	sorter;

	sorter.runLargeTest(size);
}

int	main(int argc, char **argv)
{
		char *smallTest[] = {(char *)"PmergeMe", (char *)"3", (char *)"5",
			(char *)"9", (char *)"7", (char *)"4"};

	if (argc > 1)
		testWithArgs(argc, argv);
	else
	{
		std::cout << "=== Running tests with various input sizes ===" << std::endl;
		std::cout << "\n=== Small test (5 elements) ===" << std::endl;
		testWithArgs(6, smallTest);
		std::cout << "\n=== Medium test (100 elements) ===" << std::endl;
		testWithRandomData(100);
		std::cout << "\n=== Large test (3000 elements) ===" << std::endl;
		testWithRandomData(3000);
	}
	return (0);
}

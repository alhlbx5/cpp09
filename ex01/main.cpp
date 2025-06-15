#include "RPN.hpp"

int	main(int argc, char **argv)
{
	RPN	calculator;

	if (argc != 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	if (calculator.evaluate(argv[1]))
	{
		std::cout << calculator.getResult() << std::endl;
	}
	else
	{
		std::cerr << "Error" << std::endl;
	}
	return (0);
}

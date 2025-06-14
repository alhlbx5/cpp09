#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	BitcoinExchange	exchange;

	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}
	if (!exchange.loadDatabase("data.csv"))
	{
		return (1);
	}
	exchange.processInput(argv[1]);
	return (0);
}

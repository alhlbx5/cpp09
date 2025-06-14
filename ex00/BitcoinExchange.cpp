#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	*this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		this->_data = other._data;
	}
	return (*this);
}

bool BitcoinExchange::isValidDate(const std::string &date)
{
	if (date.length() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue ;
		if (!isdigit(date[i]))
			return (false);
	}
	return (true);
}

bool BitcoinExchange::isValidValue(const float value)
{
	return (value >= 0);
}

bool BitcoinExchange::loadDatabase(const std::string &dbPath)
{
			float rate;

	std::ifstream file(dbPath.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open database file." << std::endl;
		return (false);
	}
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string date;
		std::string value;
		if (std::getline(ss, date, ',') && std::getline(ss, value))
		{
			if (!isValidDate(date))
			{
				std::cerr << "Error: invalid date format in database: " << date << std::endl;
				continue ;
			}
			std::istringstream iss(value);
			iss >> rate;
			if (!isValidValue(rate))
			{
				std::cerr << "Error: negative value in database: " << value << std::endl;
				continue ;
			}
			_data[date] = rate;
		}
	}
	file.close();
	return (true);
}

bool BitcoinExchange::processInput(const std::string &inputPath)
{
	std::ifstream file(inputPath.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (false);
	}
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		std::cout << "Processing: " << line << std::endl;
	}
	file.close();
	return (true);
}

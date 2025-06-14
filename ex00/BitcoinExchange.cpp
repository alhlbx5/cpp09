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

bool BitcoinExchange::isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool BitcoinExchange::isValidDayInMonth(int year, int month, int day)
{
	if (month < 1 || month > 12 || day < 1 || day > 31)
		return (false);
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		return (day <= 30);
	}
	else if (month == 2)
	{
		return (day <= (isLeapYear(year) ? 29 : 28));
	}
	return (true);
}

bool BitcoinExchange::isValidDate(const std::string &date)
{
	int	year;
	int	month;
	int	day;

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
	year = std::atoi(date.substr(0, 4).c_str());
	month = std::atoi(date.substr(5, 2).c_str());
	day = std::atoi(date.substr(8, 2).c_str());
	return (isValidDayInMonth(year, month, day));
}

bool BitcoinExchange::isValidValue(const float value)
{
	return (value >= 0 && value <= 1000);
}

std::string BitcoinExchange::findClosestDate(const std::string &date)
{
	std::map<std::string, float>::iterator it = _data.lower_bound(date);
	if (it != _data.end() && it->first == date)
	{
		return (date);
	}
	if (it == _data.begin())
	{
		return ("");
	}
	--it;
	return (it->first);
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
				std::cerr << "Error: invalid value in database: " << value << std::endl;
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
			float value;
	float	rate;
	float	result;

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
		std::stringstream ss(line);
		std::string date;
		std::string valueStr;
		if (std::getline(ss, date, '|') && std::getline(ss, valueStr))
		{
			date = date.substr(0, date.find_last_not_of(" \t") + 1);
			valueStr = valueStr.substr(valueStr.find_first_not_of(" \t"));
			if (!isValidDate(date))
			{
				std::cerr << "Error: bad input => " << line << std::endl;
				continue ;
			}
			try
			{
				value = std::atof(valueStr.c_str());
				if (value < 0)
				{
					std::cerr << "Error: not a positive number." << std::endl;
					continue ;
				}
				if (value > 1000)
				{
					std::cerr << "Error: too large a number." << std::endl;
					continue ;
				}
			}
			catch (...)
			{
				std::cerr << "Error: invalid value." << std::endl;
				continue ;
			}
			std::string closestDate = findClosestDate(date);
			if (closestDate.empty())
			{
				std::cerr << "Error: no valid date found in database." << std::endl;
				continue ;
			}
			rate = _data[closestDate];
			result = value * rate;
			std::cout << date << " => " << value << " = " << result << std::endl;
		}
		else
		{
			std::cerr << "Error: bad input => " << line << std::endl;
		}
	}
	file.close();
	return true;
}

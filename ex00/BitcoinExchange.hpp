#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <algorithm>
# include <exception>
# include <fstream>
# include <iostream>
# include <map>
# include <sstream>
# include <string>

class BitcoinExchange
{
  private:
	std::map<std::string, float> _data;

	bool isValidDate(const std::string &date);
	bool isValidValue(const float value);

  public:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);

	bool loadDatabase(const std::string &dbPath);
	bool processInput(const std::string &inputPath);
};

#endif

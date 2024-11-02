#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	std::cout << "An BitcoinExchange has been created!\n";
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	std::cout << "An BitcoinExchange has been created with the same qualities as another!\n";
}

BitcoinExchange &BitcoinExchange::operator =(const BitcoinExchange &copy)
{
	//if (&copy != this)
		//copy
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
	std::cout << "The BitcoinExchange has been destroyed!\n";
}

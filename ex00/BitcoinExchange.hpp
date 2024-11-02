#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>

typedef std::string str;

class BitcoinExchange
{
	private:

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);
		~BitcoinExchange();

		BitcoinExchange &operator =(const BitcoinExchange &copy);
};

#endif

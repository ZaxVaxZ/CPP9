#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>

typedef std::string str;

class BitcoinExchange
{
	private:
		std::map<str,float> database;

		bool	validFileExtension(str filename, str extension) const;
	
	public:
		BitcoinExchange();
		BitcoinExchange(str database);
		BitcoinExchange(str database, str inputfile);
		BitcoinExchange(const BitcoinExchange &copy);
		~BitcoinExchange();

		void	parseInput     (str inputfile)   ;
		void	parseDatabase  (str database)    ;
		float	getExchangeRate(str date)	const;

		BitcoinExchange &operator =(const BitcoinExchange &copy);
};

#endif

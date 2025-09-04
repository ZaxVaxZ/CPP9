#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <map>

typedef std::string str;

class BitcoinExchange
{
	private:
		
		str						_db_file, _in_file;
		std::map<str, float>	database;

		bool	isValidDate(str &date) const;
		bool	validFileExtension(str filename, str extension) const;
		bool	validString(str &s);
		bool	parseDate (str &line, str &s);
		bool	parseFloat(str &line, float &f);
		void	trim(str &line);
		str		*splitLine(str &line);

	public:
		BitcoinExchange();
		BitcoinExchange(str db_file);
		BitcoinExchange(str db_file, str in_file);
		BitcoinExchange(const BitcoinExchange &copy);
		~BitcoinExchange();

		void	parseInput     (str in_file)     ;
		void	parseDatabase  (str db_file)     ;
		float	getExchangeRate(str date)	const;

		BitcoinExchange &operator =(const BitcoinExchange &copy);
};

#endif

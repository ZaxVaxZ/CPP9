#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>

typedef std::string str;

class BitcoinExchange
{
	private:
		std::map<str,float> database;

		bool	validFileExtension(str filename, str extension) const;
		bool	validString(str &s);
		bool	parseDate (str &line, str &s);
		bool	parseFloat(str &line, float &f);
		void	trim(str &line);
		str		*splitLine(str &line);

	public:
		BitcoinExchange();
		BitcoinExchange(str database);
		BitcoinExchange(str database, str inputfile);
		BitcoinExchange(const BitcoinExchange &copy);
		~BitcoinExchange();

		void	load(std::ifstream &ifs);

		void	parseInput     (str inputfile)   ;
		void	parseDatabase  (str database)    ;
		float	getExchangeRate(str date)	const;

		BitcoinExchange &operator =(const BitcoinExchange &copy);
};

#endif

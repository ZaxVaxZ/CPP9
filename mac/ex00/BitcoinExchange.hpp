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
		bool	validString(str &s);
		bool	parseDate (str &line, str &s);
		bool	parseFloat(str &line, float &f);
		void	trim(str &line);
		str		*splitLine(str &line);

	public:
		BitcoinExchange();
		BitcoinExchange(str db_file);
		// BitcoinExchange(str db_file, str inputfile);
		BitcoinExchange(const BitcoinExchange &copy);
		~BitcoinExchange();

		void	load(std::ifstream &ifs);

		void	parseInput     (str inputfile)   ;
		void	parseDatabase  (str db_file)    ;
		float	getExchangeRate(str date)	const;

		BitcoinExchange &operator =(const BitcoinExchange &copy);
};

#endif

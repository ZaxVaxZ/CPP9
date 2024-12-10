#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(): database()
{

}

BitcoinExchange::BitcoinExchange(str database): database()
{
	if (!validFileExtension(database, ".csv"))
		throw std::runtime_error("Invalid file extension! Expected extension (.csv)");

}

BitcoinExchange::BitcoinExchange(str database, str inputfile): database()
{
	if (!validFileExtension(database, ".csv"))
		throw std::runtime_error("Invalid file extension! Expected extension (.csv)");
	if (!validFileExtension(inputfile, ".txt"))
		throw std::runtime_error("Invalid file extension! Expected extension (.txt)");

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy): database(copy.database)
{
	
}

bool BitcoinExchange::validFileExtension(str filename, str extension) const
{
	if (filename.length() < extension.length())
		return false;
	return (filename.substr(filename.length() - extension.length(), extension.length()) == extension);
}

void BitcoinExchange::parseInput(str inputfile)
{
	if (!validFileExtension(inputfile, ".txt"))
		throw std::runtime_error("Invalid file extension in (" + inputfile + ")! Expected extension (.txt)");
	if (database.empty())
	{
		std::cout << "BTC -> No Database is loaded in this object!";
		return ;
	}
}

void BitcoinExchange::parseDatabase(str database)
{
	if (!validFileExtension(database, ".csv"))
		throw std::runtime_error("Invalid file extension (" + database + ")! Expected extension (.csv)");
	if (!database.empty())
	{
		std::cout << "BTC -> A Database is already loaded in this object!";
		return ;
	}
}

float BitcoinExchange::getExchangeRate(str date) const
{

}


BitcoinExchange &BitcoinExchange::operator =(const BitcoinExchange &copy)
{
	(void) copy;
	//if (&copy != this)
		//copy
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
	
}

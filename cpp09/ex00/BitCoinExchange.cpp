/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:11:21 by pipolint          #+#    #+#             */
/*   Updated: 2025/03/11 15:42:25 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"

BTC::BTC()
{
	;
}

BTC::~BTC()
{
	;
}
BTC::BTC(const BTC& obj)
{
	(void)obj;
}

BTC	&BTC::operator=(const BTC& obj)
{
	(void)obj;
	return (*this);
}

void	BTC::open_btc_database()
{
	this->database_file.open("data.csv", std::ifstream::in);
	if (this->database_file.is_open() == false)
	{
		throw (BTC::BtcDataBaseException());
	}
}

bool	BTC::isValidYear(std::string year) const
{
	std::string	yyyy;
	std::string	mm;
	std::string	dd;

	if (std::count<std::string::iterator, char>(year.begin(), year.end(), '-') != 2)
		return (false);
	yyyy = year.substr(0, year.find_first_of('-'));
	if (yyyy.length() != 4)
	{
		std::cout << "Error: bad input => " << year << "\n";
		return (false);
	}
	mm = year.substr(year.find_first_of('-') + 1, (year.find_last_of('-') - year.find_first_of('-')) - 1);
	if (mm.length() != 2 || std::atoi(mm.c_str()) > 12)
	{
		std::cout << "Error: bad input => " << year << "\n";
		return (false);
	}
	dd = year.substr(year.find_last_of('-') + 1, std::string::npos);
	if (dd.length() != 2 || std::atoi(dd.c_str()) > 31)
	{
		std::cout << "Error: bad input => " << year << "\n";
		return (false);
	}
	return (year.find_first_not_of("0123456789-") == std::string::npos);
}

bool	BTC::isValidValue(double value) const
{
	if (value < 0)
	{
		std::cout << "Error: not a positive number\n";
		return (false);
	}
	if (value > 1000)
	{
		std::cout << "Error: value too large\n";
		return (false);
	}
	return (true);
}

void	BTC::fillDatabase()
{
	std::string	line;
	
	while (std::getline(this->database_file, line))
	{
		if (line == "date,exhange_rate" || line.empty())
			continue ;
		std::string	key = line.substr(0, line.find_first_of(','));
		double		value = static_cast<double>(std::atof(line.substr(line.find_first_of(',') + 1, std::string::npos).c_str()));
		std::pair<std::string, double>	key_value(key, value);
		this->database.insert(key_value);
	}
}

void	BTC::open_input_database(const char *const cl_arg)
{
	this->input_file.open(cl_arg, std::ifstream::in);
	if (this->input_file.is_open() == false)
		throw (InputDataBaseException());
	this->fillDatabase();
}

std::string	BTC::getYear(std::string line) const
{
	return (line.substr(0, line.find_first_of(' ')));
}

std::string	BTC::getValue(std::string line) const
{
	std::string	value;
	
	value = line.substr(line.find_first_of("|"), std::string::npos);
	return (value.substr(value.find_first_not_of("| \t"), std::string::npos));
}

std::string	BTC::validateLine(std::string& line)
{
	std::string		year;
	std::string		value; 

	if (line.find_first_not_of("0123456789-|. \t") != std::string::npos || line.find_first_of('|') == std::string::npos)	// these are the only valid characters
		return ("Error: bad input => " + line);
	if (line.find_first_of(" \t") < line.find_first_not_of(" \t"))
		line.erase(line.find_first_of(" \t"), line.find_first_not_of(" \t"));
	year = line.substr(0, line.find_first_of(' '));
	value = line.substr(line.find_first_of("|"), std::string::npos);
	if (value.find_first_not_of("| \t") == std::string::npos)
		return ("Error: bad input => " + line);
	value = value.substr(value.find_first_not_of("| \t"), std::string::npos);
	return ("");
}

void	BTC::returnDatabaseFromInput()
{
	std::string	line;
	std::string	year;
	std::map<std::string, double>::iterator	it;
	std::string	err;
	double		value;

	std::getline(this->input_file, line);
	if (line != "date | value")
	{
		std::cerr << "Error: Table has wrong header fields\n";
		return ;
	}
	while (std::getline(this->input_file, line))
	{
		err = validateLine(line);
		if (err != "")
		{
			std::cout << err << "\n";
			continue ; 
		}
		year = this->getYear(line);
		value = std::atof(this->getValue(line).c_str());
		if (!isValidYear(year) || !isValidValue(value))
			continue ;
		it = this->database.find(year);
		if (it == this->database.end())
		{
			it = this->database.lower_bound(year);
			if (it == this->database.begin())
			{
				std::cerr << "Error: Year and its lower bound doesn't exist" << " => " << line << "\n";
				continue ;
			}
			it--;
		}
		std::cout << year << " => " << value << " = " << it->second * value << "\n";
	}
}

const char*	BTC::InputDataBaseException::what() const throw()
{
	return ("Database file: Could not open input database file");
}

const char*	BTC::BtcDataBaseException::what() const throw()
{
	return ("Database file: Could not open BTC database file");
}

const char*	BTC::InvalidDatabaseHeader::what() const throw()
{
	return ("The input database has invalid header fields");
}

const char*	BTC::BadInputException::what() const throw()
{
	return ("Error: bad input");
}

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
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

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	(void) copy;	
}

bool BitcoinExchange::validString(str &s)
{
	int	i, j, k;

	for (i = 0; i < s.length() && s[i] == ' '; i++);
	for (j = i; j < s.length() && s[j] != ' '; j++);
	for (     ; j < s.length() && s[j] == ' '; j++);
	return (i != s.length() && s[i] != '\n' && (j == s.length() 
		|| (j == s.length() - 1 && line[j] == '\n')));
}

void BitcoinExchange::trim(str &line)
{
	int	i, j;

	for (i = 0; i < line.length() && line[i] == ' '; i++);
	for (j = i; j < line.length() && line[j] != ' '; j++);
	line = line.substring(i, line.length() - i);
}

bool BitcoinExchange::parseDate (str &line, str &s)
{
	if (!validString(line))
		return false;
	skipWhitespace(line);
	if (line.length() < 10)
		return false;
	for (int i = 0; i < 4; i++)
	{
		s[i] = line[i];
		if (!std::isdigit(line[i]))
			return false;
	}
	if (line[5] != '-')
		return false;
	for (int i = 0; i < 2; i++)
	{
		s[i + 6] = line[i + 6];
		if (!std::isdigit(line[i + 6]))
			return false;
	}
	if (line[8] != '-')
		return false;
	for (int i = 0; i < 2; i++)
	{
		s[i + 9] = line[i + 9];
		if (!std::isdigit(line[i + 9]))
			return false;
	}
	return true;
}

bool BitcoinExchange::parseFloat(str &line, float &f)
{
	try
	{
		f = std::stod(line)
	}
}

str *BitcoinExchange::splitLine(str &line)
{
	int	wc = 1;
	for (int i = 0; i < line.length(); i++)
		wc += (line[i] == '|');
	str *ret = new str[wc];
	int	k;
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == '|')
		{
			k++;
			continue ;
		}
		ret[k] += line[i];
	}
	return ret;
}

void BitcoinExchange::load(std::ifstream &ifs)
{
	float	f;
	bool	fail;
	str		line;
	str		date;
	str		*vals;

	fail = false;
	if (!ifs.is_open())
		return ;
	while (std::getline(ifs, line))
	{
		if (fail)
		{
			delete line;
			continue;
		}
		vals = splitLine(line);
		if (vals.length() != 2)
		{
			fail = true;
			delete vals;
			continue ;
		}
		if (!parseDate(vals[0], date) || !parseFloat(vals[1], f))
			fail = true;
		delete vals;
	}
	ifs.close();
}

BitcoinExchange &BitcoinExchange::operator =(const BitcoinExchange &copy)
{
	(void) copy;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
	
}

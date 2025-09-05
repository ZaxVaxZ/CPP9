#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(): _db_file(), _in_file(), database()
{
	
}

BitcoinExchange::BitcoinExchange(str db_file): _db_file(db_file), _in_file(), database()
{
	if (!this->validFileExtension(db_file, ".csv"))
		throw std::runtime_error("Error: Invalid file extension in `" + db_file + "`! Expected extension (.csv)");
	parseDatabase(db_file);
}

BitcoinExchange::BitcoinExchange(str db_file, str in_file): _db_file(db_file), _in_file(in_file), database()
{
	if (!this->validFileExtension(db_file, ".csv"))
		throw std::runtime_error("Error: Invalid file extension in `" + db_file + "`! Expected extension (.csv)");
	parseDatabase(db_file);
	parseInput(in_file);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy): _db_file(copy._db_file), _in_file(copy._in_file), database(copy.database)
{
	parseDatabase(copy._db_file);
	parseInput(copy._in_file);
}

bool BitcoinExchange::validFileExtension(str filename, str extension) const
{
	if (filename.length() < extension.length())
		return false;
	return (filename.substr(filename.length() - extension.length(), extension.length()) == extension);
}

bool BitcoinExchange::isValidDate(str &date) const
{
	int		year, month, day;
	char	dash;

	if (date.length() < 10 || date[4] != '-' || date[7] != '-')
		return false;
	std::stringstream ss(date);
	ss >> year >> dash >> month >> dash >> day; // >> is type aware, it knows wat goes where
	if (ss.fail())//non-numeric or xtra
		return false;
	if (year < 1970 || year > 2025)
		return false;
	if (month < 1 || month > 12 || day < 1 || day > 31)// within range
		return false;
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) //april, june, september, november
		return false;
	if (month == 2)
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
			return day <= 29; // Leap year
		else
			return day <= 28; // Non-leap year
	}
	return true;
}

bool BitcoinExchange::parseDate(str &line, str &s)
{
	if (line.length() < 10)
		throw std::runtime_error("Error: Bad date input " + line);
	for (int i = 0; i < 4; i++)
	{
		s[i] = line[i];
		if (!std::isdigit(line[i]))
			throw std::runtime_error("Error: Bad date input " + line);
	}
	if (line[4] == '/')
		line[4] = '-';
	if (line[4] != '-')
		throw std::runtime_error("Error: Bad date input " + line);
	s[4] = '-';
	for (int i = 5; i < 7; i++)
	{
		s[i] = line[i];
		if (!std::isdigit(line[i]))
			throw std::runtime_error("Error: Bad date input " + line);
	}
	if (line[7] == '/')
		line[7] = '-';
	if (line[7] != '-')
		throw std::runtime_error("Error: Bad date input " + line);
	s[7] = '-';
	for (int i = 8; i < 10; i++)
	{
		s[i] = line[i];
		if (!std::isdigit(line[i]))
			throw std::runtime_error("Error: Bad date input " + line);
	}
	for (size_t i = 10; i < line.length(); i++)
	{
		if (line[i] != ' ')
			throw std::runtime_error("Error: Bad date input " + line);
	}
	if (line.length() > 10)
		line = line.substr(0, 10);
	return true;
}

bool BitcoinExchange::parseFloat(str &line, float &f)
{
	unsigned int	i;
	bool			dec = false, negative = false;

	for (i = 0; i < line.length(); i++)
	{
		if (line[i] != ' ')
			break ;
	}
	if (line[i] == '-')
	{
		i++;
		negative = true;
	}
	if (i > 0)
		line = line.substr(i);
	for (i = 0; i < line.length(); i++)
	{
		if (line[i] == '.')
		{
			if (dec || i == line.length() - 1 || !i)
				throw std::runtime_error("Error: Second value non-numeric");
			dec = true;
			continue ;
		}
		if (!std::isdigit(line[i]))
			throw std::runtime_error("Error: Second value non-numeric");
	}
	if (negative)
		throw std::runtime_error("Error: Not a positive number");
	if (line.length() > 10 || std::atoll(line.c_str()) > INT_MAX)
		throw std::runtime_error("Error: Too large a number");
	f = std::atof(line.c_str());
	return true;
}

void BitcoinExchange::parseInput(str in_file)
{
	float	f;
	bool	fail, skip = true;
	str		line, date, amount;
	std::map<str, float>::iterator it;

	this->_in_file = in_file;
	if (this->_db_file == "")
		throw std::runtime_error("Error: No database loaded!");
	if (this->database.empty())
		parseDatabase(this->_db_file);
	std::ifstream	ifs(in_file.c_str());
	if (!ifs.is_open())
		throw std::runtime_error("Error: Could not open input file");
	fail = false;
	while (std::getline(ifs, line))
	{
		if (skip)
		{
			skip = false;
			continue;
		}
		if (std::count(line.begin(), line.end(), '|') > 1)
		{
			std::cerr << "Error: Too many items " + line << "\n";
			continue ;
		}
		if (std::count(line.begin(), line.end(), '|') < 1 || line[0] == '|' || line[line.length() - 1] == '|')
		{
			std::cerr << "Error: Bad input " + line << "\n";
			continue ;
		}
		date = line.substr(0, line.find('|'));
		amount = line.substr(line.find('|') + 1);
		try
		{
			fail = (!parseDate(date, date) || !parseFloat(amount, f));
		}
		catch(std::exception &e)
		{
			std::cerr << e.what() << '\n';
			continue;
		}
		if (fail)
		{
			std::cerr << "Error: Line has wrong number of elements\n";
			continue ;
		}
		if (!isValidDate(date))
		{
			std::cerr << "Error: Incorrect date formatting " << date << "\n";
			continue ;
		}
		it = this->database.find(date);
		if (it == this->database.end())
		{
			it = this->database.lower_bound(date);
			if (it == this->database.begin())
			{
				std::cerr  << "Error: Date earlier than lowerbound\n";
				continue;
			}
			it--;
		}
		std::cout << date << " => " << f << " = " << it->second * f << "\n";
	}
	ifs.close();
}

void BitcoinExchange::parseDatabase(str db_file)
{
	float	f;
	bool	fail, skip = true;
	str		line, date, amount;

	if (!validFileExtension(db_file, ".csv"))
		throw std::runtime_error("Error: Invalid file extension (" + db_file + ")! Expected extension (.csv)");
	if (!database.empty())
		database.clear();
	this->_db_file = db_file;
	std::ifstream	ifs(db_file.c_str());
	if (!ifs.is_open())
		throw std::runtime_error("Error: Could not open database file");
	fail = false;
	while (std::getline(ifs, line))
	{
		if (skip)
		{
			skip = false;
			continue;
		}
		if (std::count(line.begin(), line.end(), ',') > 1)
			throw std::runtime_error("Error: Too many items " + line);
		if (!fail && (std::count(line.begin(), line.end(), ',') < 1 || line[0] == ',' || line[line.length() - 1] == ','))
			throw std::runtime_error("Error: Bad input " + line);
		if (fail)
			continue ;
		date = line.substr(0, line.find(','));
		amount = line.substr(line.find(',') + 1);
		fail = (!parseDate(date, date) || !parseFloat(amount, f));
		if (!isValidDate(date))
			throw std::runtime_error("Error: Incorrect date formatting " + date);
		if (!fail)
			database[date] = f;
	}
	ifs.close();
	if (fail)
		throw std::runtime_error("Error: Improper data in database.");
}

BitcoinExchange &BitcoinExchange::operator =(const BitcoinExchange &copy)
{
	if (this != &copy)
	{
		this->_db_file = copy._db_file;
		this->_in_file = copy._in_file;
		this->database = copy.database;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
	this->database.clear();
}

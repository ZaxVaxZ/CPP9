#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(): _db_file(), _in_file(), database()
{
	
}

BitcoinExchange::BitcoinExchange(str db_file): _db_file(db_file), _in_file(), database()
{
	if (!this->validFileExtension(db_file, ".csv"))
		throw std::runtime_error("BTC -> Invalid file extension in `" + db_file + "`! Expected extension (.csv)");
	this->parseDatabase(db_file);
}

BitcoinExchange::BitcoinExchange(str db_file, str in_file): _db_file(db_file), _in_file(in_file), database()
{
	if (!this->validFileExtension(db_file, ".csv"))
		throw std::runtime_error("BTC -> Invalid file extension in `" + db_file + "`! Expected extension (.csv)");
	if (!this->validFileExtension(in_file, ".txt"))
		throw std::runtime_error("BTC -> Invalid file extension in `" + in_file + "`! Expected extension (.txt)");
	parseDatabase(db_file);
	parseInput(in_file);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy): _db_file(copy._db_file), _in_file(copy._in_file), database(copy.database)
{
	parseDatabase(db_file);
	parseInput(in_file);
}

bool BitcoinExchange::validFileExtension(str filename, str extension) const
{
	if (filename.length() < extension.length())
		return false;
	return (filename.substr(filename.length() - extension.length(), extension.length()) == extension);
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
	line = line.substring(i, j - i);
}

bool BitcoinExchange::parseDate(str &line, str &s)
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

void BitcoinExchange::parseInput(str in_file)
{
	if (!validFileExtension(in_file, ".txt"))
		throw std::runtime_error("BTC -> Invalid file extension in `" + inputfile + "`! Expected extension (.txt)");
	this->_in_file = in_file;
	if (this->_db_file == "")
		throw std::runtime_error("BTC -> No database loaded!");
	if (this->database.empty())
		parseDatabase(this->_db_file);
	
}

void BitcoinExchange::parseDatabase(str db_file)
{
	float	f;
	bool	fail;
	str		line, date, amount;

	if (!validFileExtension(db_file, ".csv"))
		throw std::runtime_error("Invalid file extension (" + db_file + ")! Expected extension (.csv)");
	if (!database.empty())
		database.clear();
	this->_db_file = db_file;
	std::ifstream	ifs(db_file);
	if (!ifs.is_open())
		throw std::runtime_error("BTS -> Could not open file");
	fail = false;
	while (std::getline(ifs, line))
	{
		fail = (fail || std::count(line.begin(), line.end(), '|') > 1 || line[0] == '|' || line[line.length() - 1] == '|');
		if (fail)
			continue ;
		date = line.substr(0, line.find('|'));
		amount = line.substr(line.find('|') + 1);
		fail = (!parseDate(date, date) || !parseFloat(amount, f));
	}
	ifs.close();
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

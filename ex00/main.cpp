#include <iostream>
#include "BitcoinExchange.hpp"

#define DATABASE "data.csv"

typedef std::string str;

bool invalid_file(char *filename)
{
	str	name(filename);

	if (name.length() < 4)
		return true;
	return (name.find(".csv") == str::npos);
}

int main(int ac, char **av)
{
	if (ac > 2)
	{
		std::cerr << "Error: Incorrect number of arguments!\n";
		std::cerr << "Usage: ./btc <filename.txt>";
		return (1);
	}
	if (ac < 2 || invalid_file(av[1]))
	{
		std::cerr << "Error: could not open file.\n";
		return (1);
	}
	
	return (0);
}

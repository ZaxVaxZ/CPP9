#include <iostream>
#include <exception>
#include "BitcoinExchange.hpp"

#define DATABASE "data.csv"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error: Incorrect number of arguments!\n";
		std::cerr << "Usage: ./btc <filename.txt>";
		return (1);
	}
	try
	{
		BitcoinExchange btc(DATABASE);
		btc.parseInput(str(av[1]));
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << "\n";
	}
	return (0);
}

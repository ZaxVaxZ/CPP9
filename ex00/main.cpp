#include <iostream>
#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error: Incorrect number of arguments!\n";
		std::cerr << "Usage: ./btc <filename.txt>";
		return (1);
	}
	
	return (0);
}

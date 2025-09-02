#include <iostream>
#include "RPN.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: ./RPN <expression>\n";
		return (1);
	}
	RPN rpn;
	try
	{
		std::cout << rpn.evaluate(av[1]) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error\n";
	}
	return (0);
}

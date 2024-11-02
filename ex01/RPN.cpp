#include "RPN.hpp"

RPN::RPN()
{
	std::cout << "An RPN has been created!\n";
}

RPN::RPN(const RPN &copy)
{
	std::cout << "An RPN has been created with the same qualities as another!\n";
}

RPN &RPN::operator =(const RPN &copy)
{
	//if (&copy != this)
		//copy
	return *this;
}

RPN::~RPN()
{
	std::cout << "The RPN has been destroyed!\n";
}

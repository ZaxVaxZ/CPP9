#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
	std::cout << "An PmergeMe has been created!\n";
}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
	std::cout << "An PmergeMe has been created with the same qualities as another!\n";
}

PmergeMe &PmergeMe::operator =(const PmergeMe &copy)
{
	//if (&copy != this)
		//copy
	return *this;
}

PmergeMe::~PmergeMe()
{
	std::cout << "The PmergeMe has been destroyed!\n";
}

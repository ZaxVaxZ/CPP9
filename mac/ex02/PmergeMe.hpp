#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>

typedef std::string str;

class PmergeMe
{
	private:

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &copy);
		~PmergeMe();

		PmergeMe &operator =(const PmergeMe &copy);
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:45:24 by pipolint          #+#    #+#             */
/*   Updated: 2025/06/15 18:57:03 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(): vector_time(0), list_time(0)
{
	
}

PmergeMe::PmergeMe(const PmergeMe& obj): vector_time(0), list_time(0)
{
	*this = obj;
}

void	PmergeMe::fillContainers(char** args)
{
	for (int i = 1; args[i]; i++)
	{
		if (!args[i][0] || std::string(args[i]).find_first_not_of("0123456789") != std::string::npos)
			throw (std::invalid_argument("Error: Only positive integers allowed in arguments!"));
		int	argInt = std::atoi(args[i]);
		if (argInt < 0)
			throw (std::invalid_argument("Error: Only positive integers allowed in arguments!"));
		this->vector.push_back(argInt);
		this->list.push_back(argInt);
		this->set.insert(argInt);
	}
	if (set.size() != vector.size())
		throw (std::invalid_argument("Error: No duplicate values allowed!"));
}

void	PmergeMe::printNumbers()
{
	for (std::vector<int>::iterator it = this->vector.begin(); it != this->vector.end(); it++)
		std::cout << (*it) << " ";
	std::cout << "\n";
}

int	PmergeMe::binaryInsertSearch(int _toInsert, size_t capIndex, std::vector<int>& searchVector)
{
	int low = 0;
	int high = capIndex;

	while (low <= high)
	{
		int middle = round((high + low) / 2);
		if (_toInsert < searchVector[middle])
			high = middle - 1;
		else
			low = middle + 1;
	}
	return (low);
}

void	PmergeMe::positionPendElements(std::vector<int>& unsorted_winners, std::vector<int>& sorted_winners, 
	std::vector<int>& losers, std::vector<int>& pendChain)
{
	for (size_t i = 0, size = sorted_winners.size(); i < size; i++)
	{
		// returns an iterator to sorted_value[i] in the unsorted_winners vector
		std::vector<int>::iterator pos = std::find(unsorted_winners.begin(), 
			unsorted_winners.end(), sorted_winners[i]);
		// get the distance from the start of the losers vector to the position
		int index = std::distance(unsorted_winners.begin(), pos);
		pendChain.push_back(losers[index]);
	}
	if (losers.size() > unsorted_winners.size())
		pendChain.push_back(losers[losers.size() - 1]);
}

void	PmergeMe::insertPend(std::vector<int>& pendChain)
{
	int					jacobsthalIndex = 3;
	long				*jacobsthal = getSequence(65);
	unsigned int		currentJacobsthal = jacobsthal[jacobsthalIndex];
	unsigned int		prevJacobsthal = jacobsthal[jacobsthalIndex - 1];
	std::vector<int>	winners = vector;
	size_t				mainChainSize = vector.size();

	// insert pend chain's first element
	if (pendChain.size())	// insert the first element
		vector.insert(vector.begin(), pendChain[0]);
	// keep inserting elements from pendChain until size of mainChain is original size + pendChain.size()
	int i = pendChain.size() - 1;
	while (vector.size() != mainChainSize + pendChain.size())
	{
		if (currentJacobsthal == prevJacobsthal)
		{
			prevJacobsthal = jacobsthal[jacobsthalIndex];
			currentJacobsthal = jacobsthal[++jacobsthalIndex];
		}
		int _toInsert = 0;
		if (pendChain.size() - 1 < static_cast<unsigned int>(jacobsthal[jacobsthalIndex]))
			_toInsert = pendChain[i--];
		else
			_toInsert = pendChain[currentJacobsthal - 1];
		// find loser's winning partner's position in the mainChain
		// get the winning pair's position in the mainChain
		std::vector<int>::iterator pairPosition = (winners.size() > currentJacobsthal - 1)
			? std::find(vector.begin(), vector.end(), winners[currentJacobsthal - 1])	// find pendChain's partner in mainChain
			: vector.end() - 1; // else winner only contains one element: use that as the pair

		// the cap should be the pendChain's jacobsthalth element's position in the main chain
		size_t	capIndex = std::distance(vector.begin(), pairPosition);
		vector.insert(vector.begin() + binaryInsertSearch(_toInsert, capIndex, vector), _toInsert);
		currentJacobsthal--;
	}
	delete [] jacobsthal;
}

std::list<int>::iterator	PmergeMe::advancedIterator(std::list<int>::iterator iterator, int advanceBy)
{
	std::advance(iterator, advanceBy);
	return (iterator);
}

int	PmergeMe::binaryInsertSearch(int _toInsert, size_t capIndex, std::list<int>& searchList)
{
	int low = 0;
	int high = capIndex;
	while (low <= high)
	{
		int middle = round((high + low) / 2);
		if (_toInsert < *advancedIterator(searchList.begin(), middle))
			high = middle - 1;
		else
			low = middle + 1;
	}
	return (low);
}

void	PmergeMe::positionPendElements(std::list<int>& unsorted_winners, std::list<int>& sorted_winners, 
	std::list<int>& losers, std::list<int>& pendChain)
{
	for (size_t i = 0, size = sorted_winners.size(); i < size; i++)
	{
		std::list<int>::iterator pos = std::find(unsorted_winners.begin(), 
			unsorted_winners.end(), *advancedIterator(sorted_winners.begin(), i));
		int index = std::distance(unsorted_winners.begin(), pos);
		pendChain.push_back(*advancedIterator(losers.begin(), index));
	}
	if (losers.size() > unsorted_winners.size())
		pendChain.push_back(losers.back());
}

void	PmergeMe::insertPend(std::list<int>& pendChain)
{
	int					jacobsthalIndex = 3;
	long				*jacobsthal = getSequence(65);
	unsigned int		currentJacobsthal = jacobsthal[jacobsthalIndex];
	unsigned int		prevJacobsthal = jacobsthal[jacobsthalIndex - 1];
	std::list<int>		winners = this->list;
	size_t				mainChainSize = list.size();

	// insert pend chain's first element
	if (pendChain.size())	// insert the first element
		list.insert(list.begin(), pendChain.front());
	// keep inserting elements from pendChain until size of mainChain is original size + pendChain.size()
	int i = pendChain.size() - 1;
	while (this->list.size() != mainChainSize + pendChain.size())
	{
		if (currentJacobsthal == prevJacobsthal)
		{
			prevJacobsthal = jacobsthal[jacobsthalIndex];
			currentJacobsthal = jacobsthal[++jacobsthalIndex];
		}
		std::list<int>::iterator pendIterator = pendChain.begin();
		if (pendChain.size() - 1 < static_cast<unsigned int>(jacobsthal[jacobsthalIndex]))
			std::advance(pendIterator, i--);
		else
			std::advance(pendIterator, currentJacobsthal - 1);
		int _toInsert = *pendIterator;
		std::list<int>::iterator pairPosition;
		if (winners.size() > currentJacobsthal - 1)
			pairPosition = std::find(this->list.begin(), this->list.end(), *advancedIterator(winners.begin(), currentJacobsthal - 1));
		else	// else winner only contains one element: use that as the pair
		{
			pairPosition = this->list.end();
			pairPosition--;
		}
		size_t	capIndex = std::distance(this->list.begin(), pairPosition);	// the cap should be the pendChain's jacobsthalth element's position in the main chain
		list.insert(advancedIterator(list.begin(), binaryInsertSearch(_toInsert, capIndex, this->list)), _toInsert);
		currentJacobsthal--;
	}
	delete [] jacobsthal;
}

long *PmergeMe::getSequence(unsigned int n) const
{
	long	*arr;

	if (!n)
		return NULL;
	if (n > 65)
		n = 65;
	arr = new long[n + 1];
	arr[0] = 0;
	arr[1] = 1;
	for (unsigned int i = 2; i < n; i++)
		arr[i] = arr[i - 1] * 2 + (1 - 2 * (i % 2 == 0));
	return arr;
}

void	PmergeMe::sortUsingVector()
{
	struct timeval		t;
	unsigned long long	micro_seconds;

	gettimeofday(&t, NULL);
	micro_seconds = t.tv_sec * 1000ull + t.tv_usec / 1000ull;
	sortVector();
	gettimeofday(&t, NULL);
	this->vector_time = t.tv_sec * 1000ull + t.tv_usec / 1000ull - micro_seconds;
}

long long	PmergeMe::getVectorTime() const
{
	return (this->vector_time);
}

void	PmergeMe::sortVector()
{
	if (this->vector.size() <= 1)
		return ;
	if (this->vector.size() == 2)
	{
		if (vector[0] > vector[1])
			std::swap(vector[0], vector[1]);
		return ;
	}

	std::vector<int>	winners;
	std::vector<int>	losers;
	std::vector<int>	pendChain;

	for (std::vector<int>::iterator it = vector.begin(); it != vector.end();)
	{
		if (it + 1 == vector.end())
		{
			losers.push_back(*it);
			break ;
		}
		if ((*it) < *(it + 1))
		{
			losers.push_back(*it);
			winners.push_back(*(it + 1));
		}
		else
		{
			winners.push_back(*it);
			losers.push_back(*(it + 1));
		}
		it += 2;
	}
	// winners vector stores the original positions of the winners
	// the cap index for the binarysearch should be where the loser's winner is with respect to whats been inserted
	this->vector = winners;
	sortVector();
	positionPendElements(winners, vector, losers, pendChain);
	insertPend(pendChain);
}

void	PmergeMe::sortUsingList()
{
	struct timeval		t;
	unsigned long long	micro_seconds;

	gettimeofday(&t, NULL);
	micro_seconds = t.tv_sec * 1000ull + t.tv_usec / 1000ull;
	sortList();
	gettimeofday(&t, NULL);
	this->list_time = t.tv_sec * 1000ull + t.tv_usec / 1000ull - micro_seconds;
}

long long	PmergeMe::getListTime() const
{
	return (this->list_time);
}

void	PmergeMe::sortList()
{
	if (this->list.size() <= 1)
		return ;
	if (this->list.size() == 2)
	{
		if (list.back() < list.front())
			std::swap(list.front(), list.back());
		return ;
	}

	std::list<int>	winners;
	std::list<int>	losers;
	std::list<int>	pendChain;

	for (std::list<int>::iterator it = list.begin(); it != list.end();)
	{
		std::list<int>::iterator curr = it;
		it++;
		if (it == list.end())
		{
			losers.push_back(*curr);
			break ;
		}
		if ((*curr) < *(it))
		{
			losers.push_back(*curr);
			winners.push_back(*it);
		}
		else
		{
			winners.push_back(*curr);
			losers.push_back(*it);
		}
		it++;
	}
	// winners vector stores the original positions of the winners
	// the cap index for the binarysearch should be where the loser's winner is with respect to whats been inserted
	this->list = winners;
	sortList();
	positionPendElements(winners, list, losers, pendChain);
	insertPend(pendChain);
}

PmergeMe	&PmergeMe::operator=(const PmergeMe& obj)
{
	this->vector = obj.vector;
	this->list = obj.list;
	this->vector_time = obj.vector_time;
	this->list_time = obj.list_time;
	return (*this);
}

PmergeMe::~PmergeMe()
{
	
}

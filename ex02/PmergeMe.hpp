/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:44:26 by pipolint          #+#    #+#             */
/*   Updated: 2025/06/15 18:51:45 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PmergeMe_HPP
# define PmergeMe_HPP

# include <iostream>
# include <vector>
# include <list>
# include <cstdlib>
# include <string>
# include <iterator>
# include <algorithm>
# include <set>
# include <cmath>
# include <ctime>
# include <sys/time.h>

class	PmergeMe
{
	private:
		unsigned int			comparisonCount;
		std::vector<int>		vector;
		std::list<int>			list;
		std::set<int>			set;
		long long				vector_time;
		long long				list_time;

		unsigned int	compareNumbers(int val1, int val2);
		void			sortVector();
		void			sortList();
		long			getJacobsthal(int n);

		// vector utility
		int		binaryInsertSearch(int _toInsert, size_t capIndex, std::vector<int>& searchVector);
		void	insertPend(std::vector<int>& pendChain);
		void	positionPendElements(std::vector<int>& unsorted_winners, std::vector<int>& sorted_winners, 
										std::vector<int>& losers, std::vector<int>& pendChain);
			
		// list utility
		std::list<int>::iterator	advancedIterator(std::list<int>::iterator iterator, int advanceBy); // this advances iterator by advanceBy

		void	printList(std::list<int>& print);
		int		binaryInsertSearch(int _toInsert, size_t capIndex, std::list<int>& searchList);
		void	positionPendElements(std::list<int>& unsorted_winners, std::list<int>& sorted_winners, 
										std::list<int>& losers, std::list<int>& pendChain);
		void	insertPend(std::list<int>& pendChain);
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe& obj);
		PmergeMe&	operator=(const PmergeMe& obj);

		void	fillContainers(char** args);
		int		size();
		
		long long		getVectorTime() const;
		long long		getListTime() const;
		unsigned int	getComparisonCount() const;
		void			sortUsingVector();
		void			sortUsingList();
		void			printNumbers();
		void			printInternalList();
		long			*getSequence(unsigned int n) const;
};

#endif
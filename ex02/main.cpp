/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:47:11 by pipolint          #+#    #+#             */
/*   Updated: 2025/06/15 18:53:29 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	PmergeMe	fordJohnson;

	if (ac < 2)
	{
		std::cerr << "<?> Usage: ./PmergeMe [Numbers]\n";
		return (1);
	}
	try
	{
		fordJohnson.fillContainers(av);
	}
	catch(std::invalid_argument& e)
	{
		std::cerr << "<!> " << e.what() << "\n";
		return (1);
	}
	std::cout << "<-> Numbers before sort:\t";
	fordJohnson.printNumbers();
	fordJohnson.sortUsingVector();
	fordJohnson.sortUsingList();
	std::cout << "<-> Numbers after sort:\t";
	fordJohnson.printNumbers();
	std::cout << "Vector sort time: " << fordJohnson.getVectorTime() << "ms\n";
	std::cout << "List sort time: " << fordJohnson.getListTime() << "ms\n";
}

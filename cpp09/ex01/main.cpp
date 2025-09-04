/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:52:58 by pipolint          #+#    #+#             */
/*   Updated: 2025/03/09 15:26:19 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: ./RPN <expression>\n";
		return (1);
	}
	double res = 0;
	try
	{
		res = RPN::calculate(av[1]);
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << e.what() << "\n";
		return (1);
	}
	std::cout << res << "\n";
}
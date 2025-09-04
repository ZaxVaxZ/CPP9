/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:57:22 by pipolint          #+#    #+#             */
/*   Updated: 2025/03/14 11:00:28 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: ./btc <database file>\n";
		return (1);
	}
	BTC			btc;

	try
	{
		btc.open_btc_database();
		btc.open_input_database(av[1]);
		btc.returnDatabaseFromInput();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << "\n";
		return (1);
	}
	// catch (BTC::BtcDataBaseException& e)
	// {
	// 	std::cerr << e.what() << "\n";
	// 	return (1);
	// }
	// catch (BTC::InputDataBaseException& e)
	// {
	// 	std::cerr << e.what() << "\n";
	// 	return (1);
	// }
}
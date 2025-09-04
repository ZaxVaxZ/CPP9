/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:53:14 by pipolint          #+#    #+#             */
/*   Updated: 2025/03/20 20:27:57 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <cstdlib>

class	RPN
{
	private:
		enum	operators
		{
			unknown = -1,
			add,
			subtract,
			multiply,
			divide
		};
	public:
		RPN();
		~RPN();
		RPN(const RPN& obj);
		RPN	&operator=(const RPN& obj);
		static RPN::operators	returnOperation(char c);
		static double			calculate(char *s);
		
};

#endif

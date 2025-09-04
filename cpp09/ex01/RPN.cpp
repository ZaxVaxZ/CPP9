/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolinta <ppolinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:39:33 by pipolint          #+#    #+#             */
/*   Updated: 2025/03/12 12:26:56 by ppolinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
	;
}

RPN::~RPN()
{
	;
}

RPN::RPN(const RPN& obj)
{
	(void)obj;
}

RPN	&RPN::operator=(const RPN& obj)
{
	(void)obj;
	return (*this);
}

RPN::operators	RPN::returnOperation(char c)
{
	if (c == '+')	return (add);
	if (c == '-')	return (subtract);
	if (c == '*')	return (multiply);
	if (c == '/')	return (divide);
	return (unknown);
}

double	RPN::calculate(char *s)
{
	std::string			input;
	std::stack<double>	stack;
	const std::string	whitespaces = " \t";
	const std::string	operators = "+-*/";
	const std::string	numbers = "0123456789";

	input = s;
	if (input.find_first_not_of(whitespaces + operators + numbers) != std::string::npos)
		throw (std::invalid_argument("Error: Invalid character used in expresion"));
	for (std::string::iterator it = input.begin(); it != input.end(); it++)
	{
		if ((*it) == '\t' || (*it) == ' ')
			continue ;
		if ((*it) >= '0' && (*it) <= '9')
		{
			if ((it != input.end()) && (*(it + 1) >= '0' && *(it + 1) <= '9'))
				throw (std::invalid_argument("Error: Numbers cannot be greater than 10"));
			stack.push(std::atof(&(*it)));
		}
		else
		{
			double	operand1 = stack.top();
			stack.pop();
			if (stack.empty())
				throw (std::invalid_argument("Error: Invalid expression"));
			double	operand2 = stack.top();
			stack.pop();
			RPN::operators	op = returnOperation((*it));
			switch(op)
			{
				case(add):
				{
					stack.push(operand2 + operand1);
					break ;
				}
				case(subtract):
				{
					stack.push(operand2 - operand1);
					break ;
				}
				case(multiply):
				{
					stack.push(operand2 * operand1);
					break ;
				}
				case(divide):
				{
					stack.push(operand2 / operand1);
					break ;
				}
				case(unknown):
					break ;
			}
		}
	}
	if (stack.size() > 1)
		throw (std::invalid_argument("Error: Invalid expression"));
	return (stack.top());
}
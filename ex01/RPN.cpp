#include "RPN.hpp"

RPN::RPN()
{

}

RPN::RPN(const RPN &copy)
{
	(void) copy;
}

RPN::Operat RPN::parseOp(char **s)
{
	if (**s == '+')
	{
		(*s)++;
		return (ADD);
	}
	if (**s == '-')
	{
		(*s)++;
		return (SUB);
	}
	if (**s == '*')
	{
		(*s)++;
		return (MULT);
	}
	if (**s == '/')
	{
		(*s)++;
		return (DIV);
	}
	return (NONE);
}

int RPN::parseNum(char **s)
{
	int		n = 1;
	long	x = 0;

	n  += -2 * (**s == '-');
	if ((**s == '-' || **s == '+') && (*(*s + 1) < '0' || *(*s + 1) > '9'))
		return (1);
	*s += (**s == '-' || **s == '+');
	if (**s < '0' || **s > '9')
		return (1);
	while (s && *s && **s >= '0' && **s <= '9')
	{
		x = x * 10 + (*(*s)++ - 48);
		if (x > 2147483647 && n == 1)
			return (0);
		if (x > 2147483648 && n == -1)
			return (0);
	}
	numbers.push(x * n);
	return (1);
}

void RPN::skipSpaces(char **s)
{
	while (s && *s && **s == ' ')
		(*s)++;
}

void RPN::error()
{
	while (!numbers.empty())
		numbers.pop();
	throw std::exception();
}

float	RPN::evaluate(char *expression)
{
	Operat	ret;
	char	*lp;
	float	ans;

	if (!expression || !*expression)
		error();
	while (*expression)
	{
		lp = expression;
		skipSpaces(&expression);
		if (!parseNum(&expression))
			error();
		ret = parseOp(&expression);
		if (lp == expression || (ret != NONE && numbers.size() < 2))
			error();
		switch (ret)
		{
			case ADD:
				ans = numbers.top();
				numbers.pop();
				ans = numbers.top() + ans;
				numbers.pop();
				numbers.push(ans);
				break;
			case SUB:
				ans = numbers.top();
				numbers.pop();
				ans = numbers.top() - ans;
				numbers.pop();
				numbers.push(ans);
				break;
			case MULT:
				ans = numbers.top();
				numbers.pop();
				ans = numbers.top() * ans;
				numbers.pop();
				numbers.push(ans);
				break;
			case DIV:
				if (numbers.top() == 0)
					error();
				ans = numbers.top();
				numbers.pop();
				ans = numbers.top() / ans;
				numbers.pop();
				numbers.push(ans);
				break;
			default:
				break;
		}
	}
	if (numbers.size() != 1)
		error();
	ans = numbers.top();
	numbers.pop();
	return (ans);
}

RPN &RPN::operator =(const RPN &copy)
{
	(void) copy;
	return *this;
}

RPN::~RPN()
{
	
}

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

typedef std::string str;

class RPN
{
	private:
		enum Operat
		{
			ADD,
			SUB,
			MULT,
			DIV,
			NONE
		};

		std::stack<float>	numbers;

		Operat	parseOp(char **s);
		int		parseNum(char **s);
		void	skipWhitespace(char **s);
		void	error();

	public:
		RPN();
		RPN(const RPN &copy);
		RPN &operator =(const RPN &copy);
		~RPN();

		float	evaluate(char *expression);
};

#endif

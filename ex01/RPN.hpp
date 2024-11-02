#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>

typedef std::string str;

class RPN
{
	private:

	public:
		RPN();
		RPN(const RPN &copy);
		~RPN();

		RPN &operator =(const RPN &copy);
};

#endif

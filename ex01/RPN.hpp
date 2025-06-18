#ifndef RPN_HPP
# define RPN_HPP

# include <cctype>
# include <exception>
# include <iostream>
# include <sstream>
# include <stack>
# include <string>

class RPN
{
  private:
	std::stack<int> _operands;

	bool isOperator(const char c);
	bool performOperation(const char op);
	bool isValidToken(const std::string &token);

  public:
	RPN();
	~RPN();
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);

	bool evaluate(const std::string &expression);
	int getResult() const;
};

#endif

#include "RPN.hpp"

RPN::RPN()
{
}

RPN::~RPN()
{
}

RPN::RPN(const RPN &other)
{
	*this = other;
}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		this->_operands = other._operands;
	}
	return (*this);
}

bool RPN::isOperator(const char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::performOperation(const char op)
{
	int	b;
	int	a;

	if (_operands.size() < 2)
	{
		return (false);
	}
	b = _operands.top();
	_operands.pop();
	a = _operands.top();
	_operands.pop();
	switch (op)
	{
	case '+':
		_operands.push(a + b);
		break ;
	case '-':
		_operands.push(a - b);
		break ;
	case '*':
		_operands.push(a * b);
		break ;
	case '/':
		if (b == 0)
		{
			return (false);
		}
		_operands.push(a / b);
		break ;
	default:
		return (false);
	}
	return (true);
}

bool RPN::evaluate(const std::string &expression)
{
			int value;

	std::istringstream iss(expression);
	std::string token;
	while (iss >> token)
	{
		if (token.length() == 1 && isOperator(token[0]))
		{
			if (!performOperation(token[0]))
			{
				return (false);
			}
		}
		else
		{
			std::istringstream tokenStream(token);
			tokenStream >> value;
			_operands.push(value);
		}
	}
	return (true);
}

int RPN::getResult() const
{
	if (_operands.empty())
	{
		return (0);
	}
	return (_operands.top());
}

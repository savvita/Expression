#include "Expression.h"

//���������� ��������� � ������ ������
bool Expression::_evaluate(std::string& expr, double& result)
{
	size_t closed;

	std::string tmp = expr;

	while ((closed = tmp.find_first_of(')')) < tmp.length())
	{
		size_t open = tmp.substr(0, closed - 1).find_last_of('(');
		if (open > tmp.length()) // �������� ������������ ������
			return false;

		double res;

		std::string sub = tmp.substr(open + 1, closed - open - 1);

		if (!this->_evaluateExpression(sub, res)) //���������� ��������� ������ ������ � �������� ������������
			return false;

		tmp.replace(open, closed - open + 1, std::to_string(res)); //������ � ������ ��������� � ������� ����������� ����������
	}

	if (tmp.find('(') < tmp.length()) // �������� ������������ ������
		return false;

	return this->_evaluateExpression(tmp, result); //��������� ���������, ������� ���������� ����� �������� ������
}

//��������� ��������� ������ ������ �� ����� � ���������, ��� ���� �������� �� ������������
bool Expression::_splitExpression(std::string& expr, List& nums, std::string& operators)
{

	std::string::iterator it = expr.begin();

	size_t length = expr.length();
	bool isOp = true; //��� �������� ������������

	while (it < expr.end())
	{
		if (isdigit(*it) || (it == expr.begin() && *it == '-')) //- ��� �������� ������������� �����
		{
			size_t i = 0;
			size_t idx = std::distance(expr.begin(), it);
			nums.enqueue(std::stod(expr.substr(idx), &i));
			it += i;
			isOp = false;
		}
		else if (*it == '+' || *it == '-')
		{
			if (isOp)
			{
				return false;
			}

			operators += *it;
			it++;
			isOp = true;
		}

		//���� ��������� ��������� � ���������� �����������, ����� �� ������������
		else if (*it == '*' || *it == '/' || *it == '^')
		{
			if (isOp)
			{
				return false;
			}

			if (std::distance(expr.begin(), it) < length - 1 && isdigit(*(it + 1)))
			{
				double num1 = nums.dequeueLast();

				size_t i = 0;

				size_t idx = std::distance(expr.begin(), it);
				double num2 = std::stod(expr.substr(idx + 1), &i);

				switch (*it)
				{
				case '*':
					nums.enqueue(num1 * num2);
					break;

				case '/':
					if (num2 == 0)
						return false;

					nums.enqueue(num1 / num2);
					break;

				case '^':
					nums.enqueue(pow(num1, num2));
					break;
				}

				it += i;
				it++;
			}
			else
			{
				return false;
			}

			isOp = false;
		}
		else
		{
			return false;
		}
	}

	return true;
}

//��������� ��������� ������ ������
bool Expression::_evaluateExpression(std::string& expr, double& result)
{
	List nums; //��� �������� �����
	std::string operators; //��� �������� ����������

	if (!this->_splitExpression(expr, nums, operators))
		return false;

	std::string::iterator it = operators.begin();

	result = nums.dequeueFirst();

	while (it < operators.end())
	{
		switch (*it)
		{
		case '+':
			result += nums.dequeueFirst();
			break;

		case '-':
			result -= nums.dequeueFirst();
			break;
		}
		it++;
	}

	return true;
}


//ctor
Expression::Expression(const std::string& expression) :expression{ expression }, _isCorrect{ false }, result{ 0.0 }
{
	this->_isCorrect = this->_evaluate(this->expression, this->result);
}


//gets
bool Expression::isCorrect() const
{
	return this->_isCorrect;
}

double Expression::getResult() const
{
	return this->result;
}

const std::string& Expression::getExpression() const
{
	return this->expression;
}



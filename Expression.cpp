#include "Expression.h"

//вычисление выражения с учетом скобок
bool Expression::_evaluate(std::string& expr, double& result)
{
	size_t closed;

	std::string tmp = expr;

	while ((closed = tmp.find_first_of(')')) < tmp.length())
	{
		size_t open = tmp.substr(0, closed - 1).find_last_of('(');
		if (open > tmp.length()) // проверка корректности скобок
			return false;

		double res;

		std::string sub = tmp.substr(open + 1, closed - open - 1);

		if (!this->_evaluateExpression(sub, res)) //вычисление выражения внутри скобок и проверка корректности
			return false;

		tmp.replace(open, closed - open + 1, std::to_string(res)); //замена в строке выражения в скобках результатом вычисления
	}

	if (tmp.find('(') < tmp.length()) // проверка корректности скобок
		return false;

	return this->_evaluateExpression(tmp, result); //вычисляем выражение, которое получилось после обрабокт скобок
}

//разбиваем выражение внутри скобок на числа и операторы, при этом проверяя на корректность
bool Expression::_splitExpression(std::string& expr, List& nums, std::string& operators)
{

	std::string::iterator it = expr.begin();

	size_t length = expr.length();
	bool isOp = true; //для проверки корректности

	while (it < expr.end())
	{
		if (isdigit(*it) || (it == expr.begin() && *it == '-')) //- для обрабоки отрицательных чисел
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

		//если встречаем операторы с повышенным приоритетом, сразу их обрабатываем
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

//вычисляем выражение внутри скобок
bool Expression::_evaluateExpression(std::string& expr, double& result)
{
	List nums; //для хранения чисел
	std::string operators; //для хранения операторов

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



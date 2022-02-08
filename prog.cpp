#include"Expression.h"

int main()
{
	//std::string expr;
	//std::cout << "Enter an expression: ";
	//getline(std::cin, expr);

	Expression* exp;

	std::string expr = "1+2*3+((1+2)*3+2/3)/2";

	exp = new Expression(expr);
	if (exp->isCorrect())
		std::cout << exp->getExpression() << " = " << exp->getResult() << "\n";
	else
		std::cout << "Incorrect\n";

	std::cout << "========================\n";

	delete exp;

	expr = "1+2*+((1+2)*3+2/3)/2";

	exp = new Expression(expr);
	if (exp->isCorrect())
		std::cout << exp->getExpression() << " = " << exp->getResult() << "\n";
	else
		std::cout << "Incorrect\n";

	std::cout << "========================\n";

	delete exp;

	expr = "1+21+2*3+2/3";
	exp = new Expression(expr);
	if (exp->isCorrect())
		std::cout << exp->getExpression() << " = " << exp->getResult() << "\n";
	else
		std::cout << "Incorrect\n";

	std::cout << "========================\n";

	delete exp;

}

#pragma once
#include<string>
#include"List.h"

class Expression
{
private:
	std::string expression;
	bool _isCorrect;
	double result;

	bool _evaluate(std::string& expr, double& result);
	bool _splitExpression(std::string& expr, List& nums, std::string& operators);
	bool _evaluateExpression(std::string& expr, double& result);

public:
	explicit Expression(const std::string& expr);

	bool isCorrect() const;

	double getResult() const;
	const std::string& getExpression() const;
};


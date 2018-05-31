#include "ExceptionList.h"

const char * VariableNotFoundException::what() const throw()
{
	return "Variable is not exist";
}

const char * InvalidExponentException::what() const throw()
{
	return "Exponent can only accept integer";
}

const char * DividedByZeroException::what() const throw()
{
	return "Divided by zero";
}

const char * InvalidFactoralException::what() const throw()
{
	return "Factoral calculation can only accept integer";
}

const char * InvalidVariableNameException::what() const throw()
{
	return "Invalid variable name";
}

const char * InvalidVariableTypeException::what() const throw()
{
	return "Invalid variable type exception";
}

const char * DuplicatedVariableNameException::what() const throw()
{
	return "This variable name has been registered";
}

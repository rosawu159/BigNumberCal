#pragma once
#pragma once
#pragma once
#include <exception>
class VariableNotFoundException : public std::exception
{
public:
	VariableNotFoundException() {};
	~VariableNotFoundException() {};
	virtual const char* what() const throw();
};

class InvalidExponentException : public  std::exception
{
public:
	InvalidExponentException() {};
	~InvalidExponentException() {};
	virtual const char* what() const throw();
};

class DividedByZeroException : public  std::exception
{
public:
	DividedByZeroException() {};
	~DividedByZeroException() {};
	virtual const char* what() const throw();
};

class InvalidFactoralException : public  std::exception
{
public:
	InvalidFactoralException() {};
	~InvalidFactoralException() {};
	virtual const char* what() const throw();
};

class InvalidVariableNameException : public  std::exception
{
public:
	InvalidVariableNameException() {};
	~InvalidVariableNameException() {};
	virtual const char* what() const throw();
};

class InvalidVariableTypeException : public  std::exception
{
public:
	InvalidVariableTypeException() {};
	~InvalidVariableTypeException() {};
	virtual const char* what() const throw();
};

class DuplicatedVariableNameException : public  std::exception
{
public:
	DuplicatedVariableNameException() {};
	~DuplicatedVariableNameException() {};
	virtual const char* what() const throw();
};



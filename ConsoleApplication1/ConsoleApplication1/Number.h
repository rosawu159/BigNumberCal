#pragma once
#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include "math.h"

#include "ExceptionList.h"
#define BASE_UNIT 100000000
#define ONE_UNIT_VECTOR_LL(num) vector<long long>{num}
using namespace std;

class Number
{
public:
	Number();
	virtual ~Number();
	friend void vecCarryBor(vector<long long> & vec); //處理進位借位
	virtual void show(ostream & outputStream)const {}
	friend vector<long long> operator*(const vector<long long> & a, const vector<long long> & b);
	friend vector<long long> operator/(const vector<long long> & a, const long long b);
	friend vector<long long> operator+(const vector<long long> & a, const vector<long long> & b);
	friend vector<long long> operator-(const vector<long long> & a, const vector<long long> & b);
	friend vector<long long> operator-(const vector<long long> & a);
	friend string processDecimal(const vector<long long> & a, const vector<long long> & b, int precision = 100);
	friend bool operator==(const vector<long long> & a, const vector<long long> & b);
	friend bool operator>(const vector<long long> & a, const vector<long long> & b);
	friend bool operator<(const vector<long long> & a, const vector<long long> & b);
	friend ostream& operator<<(ostream & outputStream, const Number& output);

};
#pragma once

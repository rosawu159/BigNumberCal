#pragma once
#pragma once
#include "Number.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

class BigInt :
	public Number
{
protected:
	vector<long long>integer;
public:
	BigInt();
	BigInt(string numStr);
	BigInt(vector<long long> num);
	BigInt(long long number);
	~BigInt();

	BigInt& operator=(const BigInt& b);
	BigInt operator+(const BigInt& b)const;
	BigInt operator-(const BigInt& b)const;
	BigInt operator-()const;
	BigInt operator*(const BigInt& b)const;
	BigInt operator/(const BigInt& b)const;
	BigInt operator/=(const BigInt& b)const;
	bool operator==(const BigInt& b)const;
	bool operator<(const BigInt& b)const;
	bool operator>(const BigInt& b)const;

	const vector<long long> & getInt()const;

	friend BigInt factoral(const BigInt& base); //�����B��
	friend BigInt power(const BigInt& base, const BigInt& exp); //�����B�� base:���ơAexp ����
	virtual void show(ostream & outputStream)const;
	friend ostream& operator<<(ostream & outputStream, const BigInt& output);
	friend istream& operator >> (istream & inputStream, BigInt& input);
};
#pragma once

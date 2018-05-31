#pragma once
#pragma once
#include "Number.h"
#include "BigInt.h"
#include "math.h"

using namespace std;

class BigDec :
	public Number
{
protected:
	vector<long long>nume; //���l
	vector<long long>deno; //����
public:
	BigDec();
	BigDec(string numStr);
	BigInt BigDec::createInt();
	BigInt BigDec::createInt_noPoint();
	BigDec(vector<long long> nume, vector<long long> deno);
	BigDec(const BigInt bigInt);
	~BigDec();


	BigDec& operator=(const BigDec& b);
	BigDec operator+(const BigDec& b)const;
	BigDec operator-(const BigDec& b)const;
	BigDec operator*(const BigDec& b)const;
	BigDec operator/(const BigDec& b)const;
	bool operator==(const BigDec& b)const;
	bool operator<(const BigDec& b)const;
	bool operator>(const BigDec& b)const;
	const vector<long long> getNume()const;
	const vector<long long> getDeno()const;
	friend BigDec powerf(const BigDec& base, const BigDec& exp);//�����B�� base:���ơAexp ����
	friend BigDec operator/(const BigInt& a, const BigInt& b);
	virtual void show(ostream & outputStream)const;
	friend ostream& operator<<(ostream & outputStream, const BigDec& output);
	friend istream& operator >> (istream & inputStream, BigDec & input);
};

#pragma once

#include "Number.h"
#include "math.h"
Number::Number()
{
}

Number::~Number()
{
}


void vecCarryBor(vector<long long> & vec)
{
	bool isMinus = (vec.back() < 0);
	if (isMinus)
	{
		vec = -vec;
	}
	for (int i = 0; i < vec.size() - 1; i++)
	{
		vec[i + 1] += vec[i] / BASE_UNIT;
		vec[i] %= BASE_UNIT;
	}
	for (int i = 0; i < vec.size() - 1; i++)
	{
		if (vec[i] < 0)
		{
			vec[i] += BASE_UNIT;
			vec[i + 1]--;
		}
	}
	if (vec.back() > BASE_UNIT)
	{
		vec.push_back(vec.back() / BASE_UNIT);
		vec[vec.size() - 2] %= BASE_UNIT;
	}
	if (isMinus)
	{
		vec = -vec;
	}
	while (vec.back() == 0 && vec.size() > 1)
	{
		vec.erase(vec.end() - 1);
	}
}



vector<long long> operator*(const vector<long long>& a, const vector<long long>& b)
{
	vector<long long> tmp(a.size() + b.size() - 1);
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < b.size(); j++)
		{
			tmp[i + j] = tmp[i + j] + (a[i] * b[j]);
		}
	}
	vecCarryBor(tmp);
	return tmp;
}

vector<long long> operator/(const vector<long long>& a, const long long b)
{
	vector<long long> temp = a;
	bool isMinus = (a.back() < 0);
	if (isMinus)
	{
		for (int i = 0; i <temp.size(); i++)
		{
			temp[i] = -temp[i];
		}
	}
	for (int i = temp.size() - 1; i>0; i--)
	{
		temp[i - 1] += (temp[i] % b) * BASE_UNIT;
		temp[i] /= b;
	}
	temp[0] /= b;
	vecCarryBor(temp);
	if (isMinus)
	{
		for (int i = 0; i <temp.size(); i++)
		{
			temp[i] = -temp[i];
		}
	}
	return temp;
}


vector<long long> operator+(const vector<long long>& a, const vector<long long>& b)
{
	vector<long long> temp;
	temp = a;
	if (temp.size() < b.size())
	{
		temp.resize(b.size());
		for (int i = 0; i < b.size(); i++)
		{
			temp[i] += b[i];
		}
	}
	else
	{
		for (int i = 0; i < b.size(); i++)
		{
			temp[i] += b[i];
		}
	}

	vecCarryBor(temp);
	return temp;
}


vector<long long> operator-(const vector<long long>& a, const vector<long long>& b)
{
	vector<long long>tempa = a;
	if (tempa.size() < b.size()) {
		tempa.resize(b.size());
	}
	for (int i = 0; i < b.size(); i++) {
		tempa[i] -= b[i];

	}
	vecCarryBor(tempa);
	return tempa;
}

vector<long long> operator-(const vector<long long>& a)
{
	vector<long long> temp(a.size());
	for (int i = 0; i < a.size(); i++)
	{
		temp[i] = -a[i];
	}
	return temp;
}
/*
vector<long long> operator*(const vector<long long>& a)
{
vector<long long> temp;
temp = a;
vector<long long> t0;
t0[0] = a[0]+a[1];

for (int i = 0; i < a.size(); i++)
{
temp[i] = -a[i];
}
return temp;
}*/


string processDecimal(const vector<long long>& a, const vector<long long>& b, int precision)
{
	vector<long long> tempNume = a;
	vector<long long> tempDeno = b;
	int digit = 0; //计计
	int divPow = 0; //埃计经Ω
	string finalResult;
	if (tempNume.back() < 0)
	{
		for (int i = 0; i < tempNume.size(); i++)
		{
			tempNume[i] = -tempNume[i];
		}
		finalResult.push_back('-');
	}
	while (!(tempDeno > tempNume / 10))
	{
		tempDeno = tempDeno * vector<long long>{10};
		divPow++;
	}
	while (digit <= precision)
	{
		long long result = 0;
		while (!(tempNume < tempDeno))
		{
			tempNume = tempNume - tempDeno;
			result++;
		}
		if (divPow > 0)
		{
			divPow--;
			tempDeno = tempDeno / 10;
		}
		else
		{
			if (digit == 1)
			{
				finalResult.push_back('.');
			}
			digit++;
			tempNume = tempNume *vector<long long>{10};
		}
		finalResult.push_back(result + '0');
	}
	return finalResult;
}


bool operator==(const vector<long long>& a, const vector<long long>& b)
{
	if (a.size() != b.size())
	{
		return false;
	}
	else {
		for (int i = 0; i < b.size(); i++) {
			if (a[i] != b[i]) {
				return false;
			}
		}
	}
	return true;
}


bool operator>(const vector<long long>& a, const vector<long long>& b)
{
	vector<long long>tempa = a;
	vector<long long>tempb = b;

	if (tempa.size() < tempb.size()) {
		tempa.resize(tempb.size());
	}
	if (tempa.size() > tempb.size()) {
		tempb.resize(tempa.size());
	}
	for (int i = tempa.size() - 1; i >= 0; i--) {
		if (tempa[i] > tempb[i]) {
			return true;
		}
		else if (tempa[i] == tempb[i]) {
			continue;
		}
		else {
			return false;
		}
	}
	return false;
}



bool operator<(const vector<long long>& a, const vector<long long>& b)
{
	if (a>b || a == b) {
		return false;
	}
	else {
		return true;
	}
}

ostream & operator<<(ostream & outputStream, const Number & output)
{
	output.show(outputStream);
	return outputStream;
}

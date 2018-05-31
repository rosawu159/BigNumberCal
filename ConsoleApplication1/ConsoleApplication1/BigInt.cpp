#include "BigInt.h"
#include "math.h"
using namespace std;

BigInt::BigInt() : Number()//�ק�b Number ���� priority �ܼơA��Ƭ�0�B�p�Ƭ�1�B�ƼƬ�2
{

}

BigInt::BigInt(string numStr) : Number()//�ק�b Number ���� priority �ܼơA��Ƭ�0
{
	//�t�ƧP�_
	bool isMinus = (numStr[0] == '-');
	if (isMinus) //16
	{
		numStr.erase(0, 1);
	}

	//stringstream�����X�r�����ƪ���O�A�ҥH�ΥL���r��B�z
	stringstream proStr;
	int pos = numStr.size();
	while (true)  //�r��B�z
	{
		if (pos - 8 > 0)
		{
			if (isMinus)
				proStr << "-";
			proStr << numStr.substr(pos - 8, 8) << " "; //��numStr���C8���Ƭ��@���A��num�ѫ᩹�e���ipro��
			pos -= 8;
		}
		else
		{
			if (isMinus)
				proStr << "-";
			proStr << numStr.substr(0, pos);//�N�ѤU����Jpro��
			break;
		}
	}

	while (!proStr.eof()) //�N�B�̧����Ʀr��J�� integer_vector���x�s
	{
		integer.push_back(0);
		proStr >> integer.back();
	}
}


BigInt::BigInt(vector<long long> num) :Number()
{
	integer = num;
}

BigInt::~BigInt()
{
}

BigInt& BigInt::operator=(const BigInt& b)
{
	(*this).integer.clear(); //�M�����Ȥ� integer
	(*this).integer = b.integer;
	return (*this);
}

BigInt::BigInt(long long number) :Number()
{
	integer.push_back(number);
	vecCarryBor(integer);
}

BigInt BigInt::operator+(const BigInt& b) const
{
	BigInt temp;
	temp.integer = (*this).integer + b.integer;
	return temp;
}


BigInt BigInt::operator-(const BigInt & b) const
{
	BigInt temp;
	temp.integer = (*this).integer - b.integer;
	return temp;
}

BigInt BigInt::operator*(const BigInt & b) const
{
	BigInt temp;
	temp.integer = (*this).integer * b.integer;
	return temp;
}


BigInt BigInt::operator/(const BigInt & b) const
{
	if (b == 0)
	{
		throw DividedByZeroException();
	}
	return BigInt(processDecimal((*this).integer, b.integer, 0));
}



bool BigInt::operator==(const BigInt & b) const
{
	return (*this).integer == b.integer;
}

bool BigInt::operator<(const BigInt & b) const
{
	return (*this).integer < b.integer;
}

bool BigInt::operator>(const BigInt & b) const
{
	return (*this).integer > b.integer;
}

BigInt BigInt::operator-()const//�t��
{
	BigInt temp = (*this);
	temp.integer = -temp.integer;
	return temp;
}


BigInt factoral(const BigInt & b)
{
	BigInt temp = b;
	BigInt base = b;

	while (base > 1)
	{
		temp = temp * (base - 1);
		base = base - 1;
	}
	return temp;
}

BigInt power(const BigInt & base, const BigInt & exp)
{
	BigInt tempbase = 1;
	BigInt tempexp = exp;
	if (tempexp == BigInt("0")) {
		return tempbase;
	}
	if (exp.getInt().back() < 0)
	{
		tempexp = -exp;
	}
	for (; tempexp > 0; tempexp = tempexp - 1) {
		tempbase = tempbase*base;
	}
	return tempbase;
}

const vector<long long> & BigInt::getInt() const
{
	return integer;
}

void BigInt::show(ostream & outputStream)const
{
	string result = processDecimal((*this).integer, vector<long long>{1}, 100);
	outputStream << result; //����X����
}


ostream & operator<<(ostream & outputStream, const BigInt & output)
{
	string result = processDecimal(output.integer, vector<long long>{1}, 100);
	outputStream << result; //����X����
	return outputStream;
}

istream & operator >> (istream & inputStream, BigInt & input)
{
	string str;
	inputStream >> str;
	input = BigInt(str);
	return inputStream;
}



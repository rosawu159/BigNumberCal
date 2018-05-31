#include "BigInt.h"
#include "math.h"
using namespace std;

BigInt::BigInt() : Number()//修改在 Number 內的 priority 變數，整數為0、小數為1、複數為2
{

}

BigInt::BigInt(string numStr) : Number()//修改在 Number 內的 priority 變數，整數為0
{
	//負數判斷
	bool isMinus = (numStr[0] == '-');
	if (isMinus) //16
	{
		numStr.erase(0, 1);
	}

	//stringstream有做出字串轉整數的能力，所以用他做字串處理
	stringstream proStr;
	int pos = numStr.size();
	while (true)  //字串處理
	{
		if (pos - 8 > 0)
		{
			if (isMinus)
				proStr << "-";
			proStr << numStr.substr(pos - 8, 8) << " "; //把numStr的每8為數為一單位，把num由後往前取進pro中
			pos -= 8;
		}
		else
		{
			if (isMinus)
				proStr << "-";
			proStr << numStr.substr(0, pos);//將剩下的放入pro中
			break;
		}
	}

	while (!proStr.eof()) //將處裡完的數字輸入至 integer_vector中儲存
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
	(*this).integer.clear(); //清除左值之 integer
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

BigInt BigInt::operator/=(const BigInt & b) const
{
	if (b == 0)
	{
		throw DividedByZeroException();
	}
	return BigInt(processInt((*this).integer, b.integer, 0));
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

BigInt BigInt::operator-()const//負數
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
	outputStream << result; //先輸出首數
}


ostream & operator<<(ostream & outputStream, const BigInt & output)
{
	string result = processDecimal(output.integer, vector<long long>{1}, 100);
	outputStream << result; //先輸出首數
	return outputStream;
}

istream & operator >> (istream & inputStream, BigInt & input)
{
	string str;
	inputStream >> str;
	input = BigInt(str);
	return inputStream;
}



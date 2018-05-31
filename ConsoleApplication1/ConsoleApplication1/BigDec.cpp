#include "BigDec.h"
#include "math.h"
using namespace std;

BigDec::BigDec() : Number()
{
	deno.push_back(1);
	nume.push_back(0);
}

BigDec::BigDec(string numStr) : Number()
{
	//璽计耞
	bool isMinus = (numStr[0] == '-');
	if (isMinus) {
		numStr.erase(0, 1);

	}

	stringstream proStr;
	int decDigit = 0;//计羆
	for (int i = 0; i < numStr.length(); i++)//埃计翴(玂痙计计)
	{
		if (numStr[i] == '.')
		{
			numStr.erase(i, 1);
			decDigit = numStr.length() - i;
			break;
		}
	}
	int pos = numStr.length();
	while (true)
	{
		if (pos - 8 > 0)
		{
			if (isMinus)
			{
				proStr << "-" + numStr.substr(pos - 8, 8) << " ";
			}
			else
			{
				proStr << numStr.substr(pos - 8, 8) << " ";
			}
			pos -= 8;
		}
		else
		{
			if (isMinus)
			{
				proStr << "-";
			}
			proStr << numStr.substr(0, pos);
			break;
		}
	}
	while (!proStr.eof()) //盢矪柑Ч计块 nume い纗
	{
		nume.push_back(0);
		proStr >> nume.back();
	}
	while (decDigit > 8)  //矪瞶だダ
	{
		deno.push_back(0);
		decDigit -= 8;
	}
	deno.push_back(pow(10, decDigit));//рだダ埃8緇计癬ㄓ讽10Ωよ
}

BigDec::BigDec(vector<long long> nume, vector<long long> deno)
{
	(*this).nume = nume;
	(*this).deno = deno;
}

BigDec::BigDec(const BigInt bigInt) :Number()
{
	nume = bigInt.getInt();
	deno.push_back((long long)1);
}

BigDec::~BigDec()
{

}

BigInt BigDec::createInt()
{
	return BigInt(processDecimal(nume, deno, 0));
}

BigDec & BigDec::operator=(const BigDec & b)
{
	nume.clear();
	deno.clear();
	(*this).nume = b.nume;
	(*this).deno = b.deno;
	return (*this);
}


BigDec BigDec::operator+(const BigDec & b) const
{
	BigDec temp;
	if ((*this).deno == b.deno)
	{
		temp.deno = (*this).deno;
		temp.nume = (*this).nume + b.nume;
		return temp;
	}
	temp.deno = (*this).deno * b.deno;
	temp.nume = (*this).nume * b.deno + (*this).deno * b.nume;
	return temp;
}


BigDec BigDec::operator-(const BigDec & b) const
{
	BigDec temp;
	if ((*this).deno == b.deno)
	{
		temp.deno = (*this).deno;
		temp.nume = (*this).nume + b.nume;
		//return temp;//辨琵搭猭タ盽
	}
	temp.deno = (*this).deno * b.deno;
	temp.nume = (*this).nume * b.deno - (*this).deno * b.nume;
	return temp;
}

BigDec BigDec::operator*(const BigDec & b) const
{
	BigDec temp;
	temp.deno = (*this).deno * b.deno;
	temp.nume = (*this).nume * b.nume;
	return temp;
}


BigDec BigDec::operator/(const BigDec & b) const
{
	BigDec temp;
	if (b == BigDec("0"))
		throw DividedByZeroException();
	temp.deno = (*this).deno * b.nume;
	temp.nume = (*this).nume * b.deno;
	if (temp.deno.back() < 0)
	{
		temp.deno = -temp.deno;
		temp.nume = -temp.nume;
	}
	return temp;
}


bool BigDec::operator==(const BigDec & b) const
{
	if ((*this).deno == b.deno)
	{
		return (*this).nume == b.nume;
	}
	return ((*this).nume * b.deno) == (b.nume * (*this).deno);
}

bool BigDec::operator<(const BigDec & b) const
{
	if ((*this).deno == b.deno)
	{
		return (*this).nume < b.nume;
	}
	return ((*this).nume * b.deno) < (b.nume * (*this).deno);
}


bool BigDec::operator>(const BigDec & b) const
{
	if ((*this).deno == b.deno)
	{
		return (*this).nume > b.nume;
	}
	return ((*this).nume * b.deno) > (b.nume * (*this).deno);
}

const vector<long long> BigDec::getNume()const
{
	return nume;
}

const vector<long long> BigDec::getDeno()const
{
	return deno;
}

BigDec powerf(const BigDec & base, const BigDec & exp)
{
	BigDec result("1.0");

	
	if (exp.nume.back() < 0)//璽计
	{
		if (BigInt(exp.deno) > -(BigInt(exp.nume))) {//璝だダだ玥<1
			string expStr = processDecimal(exp.nume, exp.deno, 0);
		}

		string expStr = processDecimal(exp.nume, exp.deno, 0);
		BigInt tempExp(expStr.substr(1, string::npos));
		while (tempExp > 0)
		{
			result = result / base;
			tempExp = tempExp - 1;
		}
	}
	else
	{

		int i = 0;
		BigDec lowtemp;
		if (BigInt(exp.deno) == BigInt("10")) {
			//だ琌き计
			BigInt a = BigInt(exp.nume);

			int num = 0;
			while (a > 0) {
				a = a - 5;
				if (a == 0) {//き计
					i = 1;
				}
				num++;
			}

			if (i == 1) {//计キよ
						 //だ㎝だダ腹埃
				base.nume;
				BigDec low = 1, high;
				string aa = processDecimal(base.nume, base.deno, 0);
				int a = aa.size();//だ
				BigDec c = sqrt(a);
				vector<long long> b;

				for (int i = 0; i < a; i++)
				{
					b.push_back(0);
				}

				for (int i = 0; i < a; i++) {
					if (a % 2 == 0) {//案计计秖
						b[i] = base.nume[2 * i] * 10 + base.nume[2 * i + 1];
					}
					else if (a % 2 != 0) {//计计秖
						if (i == 0)
							b[i] = base.nume[0];
						b[i] = base.nume[2 * i - 1] * 10 + base.nume[2 * i];
					}

				}

			}

		}

		string expStr = processDecimal(exp.nume, exp.deno, 0);
		BigInt tempExp(expStr);

		while (tempExp > 0)
		{
			result = result * base;
			tempExp = tempExp - 1;
		}


	}
	
	return result;
}

BigDec operator/(const BigInt & a, const BigInt & b)
{
	return (BigDec)a / (BigDec)b;
}

void BigDec::show(ostream & outputStream)const
{
	string result = processDecimal((*this).nume, (*this).deno, 100);
	outputStream << result;
}


ostream& operator<<(ostream & outputStream, const BigDec& output)
{
	string result = processDecimal(output.nume, output.deno, 100);
	outputStream << result;
	return outputStream;
}

istream & operator >> (istream & inputStream, BigDec & input)
{
	string str;
	inputStream >> str;
	input = BigDec(str);
	return inputStream;
}




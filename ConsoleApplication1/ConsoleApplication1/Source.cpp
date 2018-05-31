//#define TEST
#include<iostream>
#include "Number.h"
#include "BigDec.h"
#include "BigInt.h"
#include <algorithm>
#include <map>
#include <iostream>
#define MAX 256
using namespace std;

typedef BigInt Integer;
typedef BigDec Decimal;

map<string, BigInt>intVar;
map<string, BigDec>decVar;

void processInput(stringstream & ss, string& input);
BigDec calTier4(stringstream& line);
BigDec calTier3(stringstream& line);
BigDec calTier2(stringstream& line);
BigDec calTier1(stringstream& line);
bool isInt = true;

int main()
{
	string cmd;
	cout << "GO!" << endl;

#ifdef TEST
	Integer i = "123";
	Decimal d = "3.0";
	cout << i << endl << d;

	/*vector<Number*> numbers;
	numbers.push_back(&i);
	numbers.push_back(&d);
	for (const auto& num : numbers)
	{
		cout << *num << endl;
	}*/
#endif // TEST

	
	while (cmd != "EXIT")
	{
		cin >> cmd;
		getchar();
		try {
			if (cmd != "SET")
			{
				stringstream ss;
				processInput(ss, cmd);
				int t = cmd.find("=", 0);
				if (t != -1) {
					string temp = cmd.substr(0, t);
					string expr = cmd.substr(t + 1, sizeof(cmd));
					stringstream ss;
					processInput(ss, expr);
					BigDec result = calTier1(ss);

					if (intVar.count(temp))
					{
						int n = intVar.erase(temp);
						intVar.insert(pair<string, BigInt>(temp, result.createInt()));
						//cout << "variable " << temp << " = " << intVar[temp] << endl << " is sucessfuly added" << endl;
					}
					else if (decVar.count(temp))
					{
						int n = decVar.erase(temp);
						decVar.insert(pair<string, BigDec>(temp, result));
						//cout << "variable " << temp << " = " << decVar[temp] << endl << " is sucessfuly added" << endl;
					}
				}
				else {
					BigDec result = calTier1(ss);
					cout << result << endl;
				}


			}
			else if (cmd == "SET")
			{
				string type, name, expr;
				cin >> type >> name;
				getline(cin, expr);

				for (int i = 0; i < name.length(); i++)
				{
					if (name[i] == '+' || name[i] == '-' || name[i] == '*' || name[i] == '/' || name[i] == '^' ||
						name[i] == '!' || name[i] == '{' || name[i] == ')' || (name[0] >= '0' && name[0] <= '9'))
					{
						throw InvalidVariableNameException();
					}
				}
				stringstream ss;
				processInput(ss, expr);
				BigDec result = calTier1(ss);
				if (type == "int")
				{
					int n = intVar.erase(name);
					intVar.insert(pair<string, BigInt>(name, result.createInt()));
					//cout << "variable " << name << " = " << intVar[name] << endl << " is sucessfuly added" << endl;
				}
				else if (type == "dec")
				{
					int n = decVar.erase(name);
					decVar.insert(pair<string, BigDec>(name, result));
					//cout << "variable " << name << " = " << decVar[name] << endl << " is sucessfuly added" << endl;
				}

				else {
					throw InvalidVariableTypeException();
				}
			}
			else {
				cout << "Unknown command \n Plz try again." << endl;
			}
		}
		catch (DividedByZeroException e)
		{
			cout << e.what() << endl;
		}
		catch (InvalidExponentException e)
		{
			cout << e.what() << endl;
		}
		catch (InvalidFactoralException e)
		{
			cout << e.what() << endl;
		}
		catch (VariableNotFoundException e)
		{
			cout << e.what() << endl;
		}
		catch (InvalidVariableTypeException e)
		{
			cout << e.what() << endl;
		}
		catch (InvalidVariableNameException e)
		{
			cout << e.what() << endl;
		}
		catch (DuplicatedVariableNameException e)
		{
			cout << e.what() << endl;
		}
		catch (...)
		{
			cout << "Unkonwn Error";
		}
	}
	return 0;
}

void processInput(stringstream & ss, string& input)
{
	bool isUnary = true;
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == ' ')
			continue;
		if (input[i] == '(')
		{
			ss << ' ' << input[i] << ' ';
			isUnary = true;
		}
		else if (input[i] == ')')
		{
			ss << ' ' << input[i] << ' ';
			isUnary = false;
		}
		else if (input[i] == '+' || input[i] == '-' || input[i] == '*' ||
			input[i] == '/' || input[i] == '^' || input[i] == '!')
		{
			if (isUnary)
			{
				ss << "-1 * ";
			}
			else
			{
				ss << ' ' << input[i] << ' ';
				isUnary = true;
			}
		}
		//↓測試
		else if (input[i] == '.')
		{
			isInt = false;
		}
		//↑測試
		else
		{
			isUnary = false;
			ss << input[i];
		}

	}
}

BigDec calTier4(stringstream& line)
{
	BigDec lhs;
	while (line.peek() == ' ' && line.get());
	if (line.peek() == '(' && line.get())
	{
		lhs = calTier1(line);
		line.peek() == ')' && line.get();
	}
	else
	{
		string temp;
		line >> temp;
		if (temp[0] != '-' && (temp[0]<'0' || temp[0]>'9'))
		{
			if (intVar.count(temp))
			{
				lhs = intVar[temp];
			}
			else if (decVar.count(temp))
			{
				lhs = decVar[temp];
			}
			else
			{
				throw VariableNotFoundException();
			}
		}
		else
		{
			lhs = BigDec(temp);
		}
	}
	return lhs;
}

BigDec calTier3(stringstream& line)
{
	BigDec lhs = calTier4(line);
	while ((line.peek() == '^' || line.peek() == ' ' || line.peek() == '!'))
	{
		if (line.peek() == ' ')
		{
			line.get();
			continue;
		}
		if (line.get() == '^')
		{
			BigDec exp = calTier4(line);
			//if (exp - BigDec("1")>BigDec("0") || exp - BigDec("1")==BigDec("0")) 
			//{
			lhs = powerf(lhs, exp);
			//}



		}
		else
		{
			if (!(lhs == lhs.createInt()))
			{
				throw InvalidFactoralException();
			}
			lhs = factoral(processDecimal(lhs.getNume(), lhs.getDeno(), 0));
		}
	}
	return lhs;
}

BigDec calTier2(stringstream& line)
{
	BigDec lhs = calTier3(line);
	while ((line.peek() == '*' || line.peek() == '/' || line.peek() == ' '))
	{
		BigDec rhs;
		if (line.peek() == ' ')
		{
			line.get();
			continue;
		}
		if (line.get() == '*')
		{
			rhs = calTier3(line);
			lhs = lhs *rhs;
		}
		else
		{
			rhs = calTier3(line);
			if (!isInt)
			{
				lhs = lhs / rhs;
				isInt = true;
			}
			else
			{
				BigInt int_lhs = lhs.createInt();
				BigInt int_rhs = rhs.createInt();
				int_lhs /= int_rhs;
				return (BigDec)int_lhs;
			}
			
		}
	}
	return lhs;
}



BigDec calTier1(stringstream& line)
{
	BigDec lhs = calTier2(line);
	while ((line.peek() == '+' || line.peek() == '-' || line.peek() == ' '))
	{
		if (line.peek() == ' ')
		{
			line.get();
			continue;
		}
		lhs = (line.get() == '+') ? lhs + calTier2(line) : lhs - calTier2(line);
	}
	return lhs;
}

//分隔線

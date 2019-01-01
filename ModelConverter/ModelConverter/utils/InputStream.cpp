#include "InputStream.h"

using namespace std;

InputStream::InputStream()
{
}


InputStream::~InputStream()
{
}



bool InputStream::getBool(string message)
{
	bool res = false;
	do
	{
		cout << message << "(y/n)" << endl;
		string line;
		getline(cin, line);
		if (line == "y" || line == "Y" || line == "yes" || line == "YES")
		{
			res = true;
			break;
		}
		if (line == "n" || line == "N" || line == "no" || line == "NO")
		{
			res = false;
			break;
		}
		cout << "输入bool信息错误，请重新输入" << endl;
	} while (true);
	return res;
}

float InputStream::getFloat(std::string message)
{
	float res = 0;
	do
	{
		cout << message << "(浮点数)" << endl;
		string line;
		getline(cin, line);
		try
		{
			res = atof(line.c_str());
			break;
		}
		catch (const std::exception&)
		{
			cout << "输入float信息错误，请重新输入" << endl;
		}
	} while (true);
	return res;
}

string InputStream::getString(std::string message)
{
	cout << message << "(string)" << endl;
	string line;
	getline(cin, line);
	return line;
}

int InputStream::getInt(string message)
{
	int res = 0;
	do
	{
		cout << message << "(int)" << endl;
		string line;
		getline(cin, line);
		try
		{
			res = atoi(line.c_str());
			break;
		}
		catch (const std::exception&)
		{
			cout << "输入int信息错误，请重新输入" << endl;
		}
	} while (true);
	return res;
}



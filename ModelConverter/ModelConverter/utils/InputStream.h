#pragma once
#include <iostream>
#include <fstream>
#include <string>


class InputStream
{
public:
	InputStream();
	~InputStream();
	static bool getBool(std::string message);
	static float getFloat(std::string message);
	static std::string getString(std::string message);
	static int getInt(std::string message);
};


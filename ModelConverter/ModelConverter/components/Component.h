#pragma once
#include <string>
class Component
{

protected:
	int type;
	std::string name;
public:
	virtual std::string getName() {
		return name;
	};
	virtual int getType() {
		return type;
	};
	virtual std::string toString() = 0;
	virtual void getInfo() = 0;
};


#pragma once
#include "Component.h"
#include "../utils/InputStream.h"
using namespace std;
class GrowingComp :
	public Component
{

private:
	float fullGrowthTime;
	int subSteps;
public:
	GrowingComp(string name, int type) {
		this->name = name;
		this->type = type;
	};
	~GrowingComp() {};
	void getInfo() {
		this->fullGrowthTime = InputStream::getFloat("Enter full growth time: ");
		this->subSteps = InputStream::getInt("Enter number of sub-steps (1 minimum):");
	}
	string toString() {
		return  Component::getName() + "	" + 
			"fullGrowthTime:" + std::to_string(fullGrowthTime) + "	" +
			"subSteps:" + std::to_string(subSteps);
	}
};


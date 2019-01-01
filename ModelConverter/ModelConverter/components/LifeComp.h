#pragma once
#include "Component.h"
#include "../utils/InputStream.h"
using namespace std;
class LifeComp :
	public Component
{

private:
	int deathAnimId;
	int parentID;
	float breedMaturity;
	float averageBreedTime;
	float averagePopulation;
	float averageLifeLength;

public:
	LifeComp(string name, int type) {
		this->name = name;
		this->type = type;
	};
	~LifeComp() {};
	void getInfo() {
		this->deathAnimId = InputStream::getInt("Enter ID of standard death animation: ");
		this->parentID = InputStream::getInt("Enter parent ID: ");
		this->breedMaturity = InputStream::getFloat("Enter breeding maturity age: ");
		this->averageBreedTime = InputStream::getFloat("Enter average breed time: ");
		this->averagePopulation = InputStream::getFloat("Enter average population: ");
		this->averageLifeLength = InputStream::getFloat("Enter average life length (you need to calc first!): ");
	}
	string toString() {
		return  Component::getName() + "	" + 
			"deathAnimId:" + std::to_string(deathAnimId) + "	" +
			"parentID:" + std::to_string(parentID) + "	" +
			"breedMaturity:" + std::to_string(breedMaturity) + "	" +
			"averageBreedTime:" + std::to_string(averageBreedTime) + "	" +
			"averagePopulation:" + std::to_string(averagePopulation) + "	" +
			"averageLifeLength:" + std::to_string(averageLifeLength);
	}
};


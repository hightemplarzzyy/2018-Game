#pragma once
#include "Component.h"
#include "../utils/InputStream.h"
using namespace std;
class EatingComp :
	public Component
{

private:
	int maxHungerPoints;
	float hungerPerDay;
	int foodClassification;
	int aiId;
public:
	EatingComp(string name, int type) {
		this->name = name;
		this->type = type;
	};
	~EatingComp() {};
	void getInfo() {
		this->maxHungerPoints = InputStream::getInt("Max hunger points:");
		this->hungerPerDay = InputStream::getFloat("Hunger points lost per day :");
		this->foodClassification = InputStream::getInt("Classification ID of edible food:");
		this->aiId = InputStream::getInt("Eating AI ID:");
	}

	string toString() {
		return  Component::getName() + "	" +
			"maxHungerPoints:" + std::to_string(maxHungerPoints) + "	" +
			"hungerPerDay:" + std::to_string(hungerPerDay) + "	" +
			"foodClassification:" + std::to_string(foodClassification) + "	" +
			"aiId:" + std::to_string(aiId);
	}
};


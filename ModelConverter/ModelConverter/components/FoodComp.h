#pragma once
#include "Component.h"
#include "../utils/InputStream.h"
using namespace std;
class FoodComp :
	public Component
{

private:
	int classificationId;
	int foodPoints;
public:
	FoodComp(string name, int type) {
		this->name = name;
		this->type = type;
	};
	~FoodComp() {};
	void getInfo() {
		this->classificationId = InputStream::getInt("Enter the classification ID: ");
		this->foodPoints = InputStream::getInt("Enter food points: ");
	}
	string toString() {
		return  Component::getName() + "	" +
			"classificationId:" + std::to_string(classificationId) + "	" +
			"foodPoints:" + std::to_string(foodPoints);
	}
};


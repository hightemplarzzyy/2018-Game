#pragma once
#include "Component.h"
#include "../utils/InputStream.h"
using namespace std;
class InfoComp :
	public Component
{

private:
	string entityName;
	string description;
	int dpCost;
	int dpPerMin;
	float roamingRange;
	string iconFile;
	string soundFile;

public:
	InfoComp(string name, int type) {
		this->name = name;
		this->type = type;
	};
	~InfoComp() {};
	void getInfo() {
		this->entityName = InputStream::getString("Enter entity name: ");
		this->description = InputStream::getString("Enter description: ");
		this->dpCost = InputStream::getInt("Enter dp cost: ");
		this->dpPerMin = InputStream::getInt("Enter base dp/min: ");
		this->roamingRange = InputStream::getFloat("Enter roaming range: ");
		this->iconFile = InputStream::getString("Enter icon file name (without extention): ");
		this->soundFile = InputStream::getString("Enter placement sound file name(without extention) : ");
	}

	string toString() {
		return  Component::getName() + "	" + 
			"entityName:" + entityName + "	" +
			"description:" + description + "	" +
			"dpCost:" + std::to_string(dpCost) + "	" +
			"dpPerMin:" + std::to_string(dpPerMin) + "	" +
			"roamingRange:" + std::to_string(roamingRange) + "	" +
			"iconFile:" + iconFile + "	" +
			"soundFile:" + soundFile;
	}
};


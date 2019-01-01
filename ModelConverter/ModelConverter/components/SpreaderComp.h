#pragma once
#include "Component.h"
#include "../utils/InputStream.h"
using namespace std;
class SpreaderComp :
	public Component
{

private:
	int biome;
	int strength;
	int distance;

public:
	SpreaderComp(string name, int type) {
		this->name = name;
		this->type = type;
	};
	void getInfo() {
		this->biome = InputStream::getInt("Enter biome ID: ");
		this->strength = InputStream::getInt("Enter strength: ");
		this->distance = InputStream::getInt("Enter range: ");
	}
	string toString() {
		return  Component::getName() + "	" + 
			"biome:" + std::to_string(biome) + "	" +
			"strength:" + std::to_string(strength) + "	" +
			"distance:" + std::to_string(distance);
	}
};

#pragma once

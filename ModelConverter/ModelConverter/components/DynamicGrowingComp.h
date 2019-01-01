#pragma once
#include "Component.h"
#include "../utils/InputStream.h"
class DynamicGrowingComp :
	public Component
{

private:
	 float fullGrownTime = 0;
public:
	DynamicGrowingComp(string name, int type) {
		this->name = name;
		this->type = type;
	};
	~DynamicGrowingComp() {};
	void getInfo() {
		this->fullGrownTime = InputStream::getFloat("DynamicGrowing component µÄfullGrownTime");
	}

	string toString() {
		return Component::getName() + "	" +
			  "fullGrownTime:" + std::to_string(fullGrownTime);
	}
};


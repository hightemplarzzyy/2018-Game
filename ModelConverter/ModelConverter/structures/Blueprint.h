#pragma once
#include <iostream>
#include <string>
#include "SubBlueprint.h"
#include "../components/ComponentFactor.h"
#include <vector>
#include <map>
class Blueprint
{
public:
	Blueprint();
	~Blueprint();
	bool underWater, overWater;
	void loadModelInfo();
	void getComponents();
	void exportBlueprint();
	int rgbToFloat(string rgb);
private:
	vector<SubBlueprint*> subBlueprints;
	vector<Component*> components;
	map<string, Material> materialsCache;
	bool isCostomMaterial = false;
	Vec3 baseColour1;
	Vec3 baseColour2;
};


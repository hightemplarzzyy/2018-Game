#pragma once
#include "ModelSection.h"
#include <vector>
using namespace std;
class SubBlueprint
{
public:
	SubBlueprint();
	~SubBlueprint();
	void addSection(ModelSection* section);
	void setMin(Vec3 min);
	void setMax(Vec3 max);
	Vec3 getMin();
	Vec3 getMax();
	int getVertexCount();
	vector<ModelSection*> getSections();
private:
	vector<ModelSection*> sections;
	Vec3 min, max;
};
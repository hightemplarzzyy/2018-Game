#include "SubBlueprint.h"
SubBlueprint::SubBlueprint()
{
}

SubBlueprint::~SubBlueprint()
{
}

void SubBlueprint::addSection(ModelSection* section)
{
	sections.push_back(section);
}

void SubBlueprint::setMin(Vec3 min)
{
	this->min = min;
}

void SubBlueprint::setMax(Vec3 max)
{
	this->max = max;
}

Vec3 SubBlueprint::getMin()
{
	return min;
}

Vec3 SubBlueprint::getMax()
{
	return max;
}

int SubBlueprint::getVertexCount()
{
	int res = 0;
	for (int i = 0; i < sections.size(); i++)
	{
		res += sections[i]->getVertexCount();
	}
	return res;
}

vector<ModelSection*> SubBlueprint::getSections()
{
	//unsafe, need to improve
	const vector<ModelSection*> unmodifiedSection = sections;
	return unmodifiedSection;
}

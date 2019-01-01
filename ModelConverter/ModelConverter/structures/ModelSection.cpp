#include "ModelSection.h"
ModelSection::ModelSection(Material* material)
{
	this->material = material;
}

void ModelSection::addTriangle(Triangle triangle)
{
	triangles.push_back(triangle);
}

int ModelSection::getVertexCount()
{
	return triangles.size() * 3;
}

Material * ModelSection::getMaterial()
{
	return material;
}

vector<Triangle> ModelSection::getTriangles()
{
	return vector<Triangle>(triangles);
}


ModelSection::~ModelSection()
{
}

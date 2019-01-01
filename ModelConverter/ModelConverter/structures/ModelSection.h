#pragma once
#include "Material.h"
#include "Triangle.h"
#include "vector"
using namespace std;

class ModelSection
{
public:
	ModelSection(Material* material);
	void addTriangle(Triangle triangle);
	int getVertexCount();
	Material* getMaterial();
	vector<Triangle> getTriangles();
	~ModelSection();
	
private:
	Material* material;
	vector<Triangle> triangles;
};


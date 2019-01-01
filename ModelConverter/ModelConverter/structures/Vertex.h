#pragma once
#include "Vec3.h"
class Vertex
{
public:
	Vertex(Vec3 position, Vec3 normal);
	Vertex() {};
	~Vertex();
	Vec3 getPosition();
	Vec3 getNormal();
	
private:
	Vec3 position;
	Vec3 normal;
};


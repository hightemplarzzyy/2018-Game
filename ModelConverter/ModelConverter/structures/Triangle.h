#pragma once
#include "Vertex.h"
#include <string>

class Triangle
{
public:
	Triangle() {};
	Triangle(Vertex p0, Vertex p1, Vertex p2);
	std::string toString();
	~Triangle();
private:
	Vertex p0, p1, p2;
};


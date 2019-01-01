#include "Triangle.h"



Triangle::Triangle(Vertex p0, Vertex p1, Vertex p2)
{
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;
}

std::string Triangle::toString()
{
	std::string P0 = "P0:" + std::to_string(p0.getNormal().getX()) + "," + std::to_string(p0.getNormal().getY()) + "," + std::to_string(p0.getNormal().getZ()) + ","
		+ std::to_string(p0.getPosition().getX()) + "," + std::to_string(p0.getPosition().getY()) + "," + std::to_string(p0.getPosition().getZ()) + "  ";

	std::string P1 = "P1:" + std::to_string(p1.getNormal().getX()) + "," + std::to_string(p1.getNormal().getY()) + "," + std::to_string(p1.getNormal().getZ()) + ","
		+ std::to_string(p1.getPosition().getX()) + "," + std::to_string(p1.getPosition().getY()) + "," + std::to_string(p1.getPosition().getZ()) + "  ";

	std::string P2 = "P2:" + std::to_string(p2.getNormal().getX()) + "," + std::to_string(p2.getNormal().getY()) + "," + std::to_string(p2.getNormal().getZ()) + ","
		+ std::to_string(p2.getPosition().getX()) + "," + std::to_string(p2.getPosition().getY()) + "," + std::to_string(p2.getPosition().getZ());
	return P0 + P1 + P2;
}


Triangle::~Triangle()
{
}

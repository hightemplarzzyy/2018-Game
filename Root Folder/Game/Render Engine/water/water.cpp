#include "water.h"

float Water::SQUARE_SIZE = 1.0f;
float Water::AMPLITUDE = 0.06f;

Water::Water(float x, float z, float height, float size)
{
	vao = 0;
	this->x = x;
	this->z = z;
	this->height = height;
	this->pointCount = (int)(size / SQUARE_SIZE + 1);
}
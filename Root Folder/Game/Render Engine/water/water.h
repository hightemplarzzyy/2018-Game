#pragma once

#include "watergenerator.h"
#include <vector>

class Water
{
public:
	static float SQUARE_SIZE;
	static float AMPLITUDE;

	int pointCount;
	float height;
	float x, z;
	unsigned int vao;
	int vertexCount;

public:
	Water() = default;
	Water(float x, float z, float height, float size);
};
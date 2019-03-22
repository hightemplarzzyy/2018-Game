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

	Water(float x, float z, float height, float size)
	{
		vao = 0;
		this->x = x;
		this->z = z;
		this->height = height;
		this->pointCount = (int)(size / SQUARE_SIZE + 1);
	}
};

float Water::SQUARE_SIZE = 1.0f;
float Water::AMPLITUDE = 0.06f;
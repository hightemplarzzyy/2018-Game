#pragma once

#include <vector>
#include "water.h"
#include "../toolbox/maths/maths_func.h"

class WaterGenerator 
{
public:
	static int VERTICES_PER_SQUARE;// 2 triangles
	static int VERTEX_SIZE_BYTES;// x,z position + indicator

public:
	static std::vector<float> generate(int gridCount, float waterHeight);

private:
	static std::vector<vec2> calculateCornerPositions(int col, int row);
	static void storeTriangle(std::vector<vec2> &cornerPos, bool left, bool normalSquare, float waterHeight, std::vector<float> &data);
	static bool isUnderGround(vec2 vert1, vec2 vert2, vec2 vert3, float waterHeight);
	static bool isVertexUnderGround(vec2 point, float waterHeight);
	static void storeVertex(vec2 currentVertex, vec2 vertex1, vec2 vertex2, std::vector<float> &data);
};
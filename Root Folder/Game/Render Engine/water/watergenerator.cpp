#include "watergenerator.h"

int WaterGenerator::VERTICES_PER_SQUARE = 3 * 2;
int WaterGenerator::VERTEX_SIZE_BYTES = 6;

std::vector<float> WaterGenerator::generate(int gridCount, float waterHeight)
{
	int totalVertexCount = gridCount * gridCount * VERTICES_PER_SQUARE;
	std::vector<float> data;
	for (int row = 0; row < gridCount; row++)
		for (int col = 0; col < gridCount; col++)
		{
			std::vector<vec2> cornerPos = calculateCornerPositions(col, row);
			bool even = (col + row) % 2 == 0;
			storeTriangle(cornerPos, true, even, waterHeight, data);
			storeTriangle(cornerPos, false, even, waterHeight, data);
		}

	return data;
}

std::vector<vec2> WaterGenerator::calculateCornerPositions(int col, int row)
{
	std::vector<vec2> vertices;
	vertices.push_back(vec2(col, row));
	vertices.push_back(vec2(col, row + 1));
	vertices.push_back(vec2(col + 1, row));
	vertices.push_back(vec2(col + 1, row + 1));
	return vertices;
}

void WaterGenerator::storeTriangle(std::vector<vec2> &cornerPos, bool left, bool normalSquare, float waterHeight, std::vector<float> &data)
{
	int index0 = left ? 0 : 2;
	int index1 = (!normalSquare && !left) ? 0 : 1;
	int index2 = (normalSquare && left) ? 2 : 3;
	if (!isUnderGround(cornerPos[index0], cornerPos[index1], cornerPos[index2], waterHeight))
	{
		vec2 v0 = cornerPos[index0];
		vec2 v1 = cornerPos[index1];
		vec2 v2 = cornerPos[index2];
		storeVertex(v0, v1, v2, data);
		storeVertex(v1, v2, v0, data);
		storeVertex(v2, v0, v1, data);
	}
}

bool WaterGenerator::isUnderGround(vec2 vert1, vec2 vert2, vec2 vert3, float waterHeight)
{
	return isVertexUnderGround(vert1, waterHeight)
		&& isVertexUnderGround(vert2, waterHeight)
		&& isVertexUnderGround(vert3, waterHeight);
}

bool WaterGenerator::isVertexUnderGround(vec2 point, float waterHeight)
{
	//TODO 对接地形
	//float terrainHeight = heightFinder.getHeight(point.x, point.y);
	float terrainHeight = 100000000.0f;
	return false;
}

void WaterGenerator::storeVertex(vec2 currentVertex, vec2 vertex1, vec2 vertex2, std::vector<float> &data)
{
	data.push_back(currentVertex.x);
	data.push_back(currentVertex.y);

	vec2 offset1 = vertex1 - currentVertex;
	vec2 offset2 = vertex2 - currentVertex;
	data.push_back(offset1.x); data.push_back(offset1.y);
	data.push_back(offset2.x); data.push_back(offset2.y);
}
#include "NormalsGenerator.h"

void NormalsGenerator::generateNormals(const std::vector<std::vector<float>> &heights, std::vector<std::vector<vec3>> &normals) {
	normals.resize(heights.size(), std::vector<vec3>(heights.size()));
	for (int z = 0; z < normals.size(); z++) {
		for (int x = 0; x < normals.size(); x++) {
			normals[z][x] = calculateNormal(x, z, heights);
		}
	}
}

vec3 NormalsGenerator::calculateNormal(int x, int z, std::vector<std::vector<float>> heights) {
	float heightL = getHeight(x - 1, z, heights);
	float heightR = getHeight(x + 1, z, heights);
	float heightD = getHeight(x, z - 1, heights);
	float heightU = getHeight(x, z + 1, heights);

	vec3 normal = vec3(heightL - heightR, 2.0f, heightD - heightU, true);

	return normal;
}

float NormalsGenerator::getHeight(int x, int z, std::vector<std::vector<float>> heights) {
	x = x < 0 ? 0 : x;
	z = z < 0 ? 0 : z;
	x = x >= heights.size() ? heights.size() - 1 : x;
	z = z >= heights.size() ? heights.size() - 1 : z;

	return heights[z][x];
}

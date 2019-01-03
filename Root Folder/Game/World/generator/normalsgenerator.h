#pragma once
#include "..\..\Render Engine\toolbox\maths\vec3.h"
#include <vector>

using namespace std;

class NormalsGenerator {
public:
	static void generateNormals(const std::vector<std::vector<float>> &heights, std::vector<std::vector<vec3>> &normals);
private:
	static vec3 calculateNormal(int x, int z, vector<vector<float>> heights);
	static float getHeight(int x, int z, vector<vector<float>> heights);
};
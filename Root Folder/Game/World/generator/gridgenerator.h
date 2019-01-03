#pragma once
#include <vector>
#include "..\..\Render Engine\toolbox\maths\vec3.h"

using namespace std;
class GridGenerator {
public:
	static vector<vec3u> generateGridIndexBuffer(int vertexCount, bool even);
private:
	static int storeQuad1(vector<vec3u>& indices, int pointer, int topLeft, int topRight, int bottomLeft, int bottomRight, bool mixed);
	static int storeQuad2(vector<vec3u>& indices, int pointer, int topLeft, int topRight, int bottomLeft, int bottomRight, bool mixed);
};
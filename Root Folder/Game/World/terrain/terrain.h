#pragma once
#include <vector>
#include "..\..\Render Engine\toolbox\maths\vec3.h"
#include "..\..\Render Engine\toolbox\color.h"
#include "..\..\Render Engine\buffers\vertexarray.h"
#include "..\..\Render Engine\buffers\indexbuffer.h"

using namespace std;

//地形 一个CHUNK大小
class Terrain {
public:
	static const int GRID_COUNT;
	static const int VERTEX_COUNT;
	static const int SIZE;
	static const int GRID_SQUARE_SIZE;

	VertexArray *m_Vao;
	IndexBuffer *m_Ibo;
	vector<vec3u> m_Indices;

	vector<vec3> m_Positions;
	vector<vec3> m_Normals;
	vector<vec3> m_Colors;

public:
	Terrain();
	Terrain(int gridX, int gridZ, const vector<vector<float>> &_heights, const vector<vector<vec3>> &_normals, const vector<vector<Color>> &_colors);
	vector<vec3> generatePositionsVector(int gridX, int gridZ, const vector<vector<float>> &_heights);
	vector<vec3> generateNormalsVector(int gridX, int gridZ, const vector<vector<vec3>> &_normals);
	vector<vec3> generateColorsVector(int gridX, int gridZ, const vector<vector<Color>> &_colors);

	VertexArray* getVAO();
	IndexBuffer* getIBO();

	void bindVAO();
	void unbindVAO();
};
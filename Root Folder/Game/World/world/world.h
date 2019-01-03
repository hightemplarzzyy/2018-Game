#pragma once
#pragma once
#include "..\..\Render Engine\toolbox\color.h"
#include "..\world config\worldconfigs.h"
#include "..\terrain\terrain.h"
#include "..\generator\perlinnoisegenerator.h"

using namespace std;

class World {
public:
	static const Color BACK_COLOR;           //地形颜色
	static const int CHUNK_COUNT = 5;        //地形分为5*5块
	static const int SIZE = 100;             //地形大小
	static const int MAX_ALTITUDE = 8;       //最高海拔
	static const int DESIRED_VERTEX_COUNT = 138;  //每个方向138个顶点?

private:
	WorldConfigs m_Configs;
	vector<vector<Terrain>> m_Terrains;

public:
	World(const WorldConfigs &_configs);
	Terrain getTerrain(int gridX, int gridZ);
	vector<vector<Terrain>> getTerrains();
	WorldConfigs getWorldConfigs();
private:
	float generateHeights(vector<vector<float>> &heights, PerlinNoiseGenerator noise);
	void generateTerrains(const vector<vector<float>> &heights, const vector<vector<vec3>> &normals);
	void generateTerrain(int gridX, int gridZ, int chunkLength, const vector<vector<float>> &heights, const vector<vector<vec3>> &normals);
};
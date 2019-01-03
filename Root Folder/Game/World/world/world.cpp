#include "World.h"
#include "..\generator\normalsgenerator.h"
#include "..\generator\colorcalculator.h"
#include "..\generator\perlinnoisegenerator.h"

const Color World::BACK_COLOR = Color(111.0f, 80.0f, 45.0f, true);

World::World(const WorldConfigs &_configs) {
	m_Configs = _configs;
	PerlinNoiseGenerator noise(m_Configs.getSeed(), m_Configs.getSmoothness(), m_Configs.getVertexCount() - 1.0f, m_Configs.getWaterHeight() + WorldConfigs::EDGE_ABOVE_WATER);

	//heights
	vector<vector<float>> heights(m_Configs.getVertexCount(), vector<float>(m_Configs.getVertexCount()));
	float maxHeight = generateHeights(heights, noise);
	m_Configs.setMaxHeight(maxHeight);

	//normals
	vector<vector<vec3>> normals;
	NormalsGenerator::generateNormals(heights, normals);

	//terrains
	m_Terrains.resize(CHUNK_COUNT, vector<Terrain>(CHUNK_COUNT));
	generateTerrains(heights, normals);
}

float World::generateHeights(vector<vector<float>>& heights, PerlinNoiseGenerator noise) {
	float maxHeight = 0.0f;
	for (int z = 0; z < heights.size(); z++) {
		for (int x = 0; x < heights.size(); x++) {
			heights[z][x] = noise.getPerlinNoise(x, z);
			maxHeight = fmaxf(maxHeight, heights[z][x]);
		}
	}
	return maxHeight;
}

void World::generateTerrains(const vector<vector<float>> &heights, const vector<vector<vec3>> &normals) {
	int chunkLength = (heights.size() - 1) / m_Terrains.size() + 1;
	for (int i = 0; i < m_Terrains.size(); i++) {
		for (int j = 0; j < m_Terrains.size(); j++) {
			generateTerrain(i, j, chunkLength, heights, normals);
		}
	}
}

void World::generateTerrain(int gridX, int gridZ, int chunkLength, const vector<vector<float>> &heights, const vector<vector<vec3>> &normals) {
	vector<vector<float>> childHeights(chunkLength, vector<float>(chunkLength));
	vector<vector<vec3>> childNormals(chunkLength, vector<vec3>(chunkLength));
	vector<vector<Color>> childColors(chunkLength, vector<Color>(chunkLength));

	ColorCalculator colorcalculator;

	int startX = gridZ * (chunkLength - 1);
	int startZ = gridX * (chunkLength - 1);

	for (int z = 0; z < chunkLength; z++) {
		for (int x = 0; x < chunkLength; x++) {
			childHeights[z][x] = heights[startZ + z][startX + x];
			childNormals[z][x] = normals[startZ + z][startX + x];
			childColors[z][x] = colorcalculator.getColor(childHeights[z][x], m_Configs);
		}
	}

	m_Terrains[gridX][gridZ] = Terrain(gridZ, gridX, childHeights, childNormals, childColors);
}

Terrain World::getTerrain(int gridX, int gridZ) {
	if (gridX < 0 || gridX >= m_Terrains.size() || gridZ < 0 || gridZ >= m_Terrains.size()) {
		return Terrain();
	}
	return m_Terrains[gridZ][gridX];
}

vector<vector<Terrain>> World::getTerrains() {
	return m_Terrains;
}

WorldConfigs World::getWorldConfigs() {
	return m_Configs;
}

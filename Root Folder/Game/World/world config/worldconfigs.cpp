#include "worldConfigs.h"
#include "..\..\Render Engine\toolbox\maths\maths_func.h"

float WorldConfigs::EDGE_ABOVE_WATER = 0.5f;

WorldConfigs::WorldConfigs(int seed, float smoothness, int vertexCount, float waterHeight) {
	this->m_seed = seed;
	this->m_smoothness = smoothness;
	this->m_vertexCount = vertexCount;
	this->m_waterHeight = waterHeight;
}

WorldConfigs::WorldConfigs() {
	this->m_seed = Maths::randomInt(1000000);
	this->m_smoothness = 1.0f;
	this->m_vertexCount = 136;
	this->m_waterHeight = -2.0f;
}

int WorldConfigs::getSeed() {
	return m_seed;
}

int WorldConfigs::getVertexCount() {
	return m_vertexCount;
}

float WorldConfigs::getSmoothness() {
	return m_smoothness;
}

float WorldConfigs::getWaterHeight() {
	return m_waterHeight;
}

float WorldConfigs::getMaxHeight() {
	return m_maxHeight;
}

void WorldConfigs::setMaxHeight(float height) {
	m_maxHeight = height;
}

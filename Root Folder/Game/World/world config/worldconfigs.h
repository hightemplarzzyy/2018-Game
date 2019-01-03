#pragma once

class WorldConfigs {
private:
	int m_seed;
	int m_vertexCount;
	float m_smoothness;
	float m_waterHeight;
	float m_maxHeight;

public:
	static float EDGE_ABOVE_WATER;

	WorldConfigs();
	WorldConfigs(int seed, float smoothness, int vertexCount, float waterHeight);

	int getSeed();
	int getVertexCount();
	float getSmoothness();
	float getWaterHeight();
	float getMaxHeight();

	void setMaxHeight(float height);
};
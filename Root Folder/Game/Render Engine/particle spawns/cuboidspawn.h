#pragma once

#include "ParticleSpawn.h"

class CuboidSpawn :public ParticleSpawn {
private:
	float m_xScale;
	float m_yScale;
	float m_zScale;
	float m_yOffset;

public:
	CuboidSpawn(float xScale, float yScale, float zScale) {
		m_xScale = xScale;
		m_yScale = yScale;
		m_zScale = zScale;
		m_yOffset = 0.0f;
	}

	CuboidSpawn(float xScale, float yScale, float zScale, float yOffset) {
		m_xScale = xScale;
		m_yScale = yScale;
		m_zScale = zScale;
		m_yOffset = yOffset;
	}

	virtual vec4 getBaseSpawnPosition() {
		float xOffset = float(rand() % 100) / 100 * m_xScale;
		float yOffset = float(rand() % 100) / 100 * m_yScale + m_yScale;
		float zOffset = float(rand() % 100) / 100 * m_zScale;
		return vec4(xOffset, yOffset, zOffset,1.0f);
	}
};
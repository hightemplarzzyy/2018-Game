#include "PerlinNoiseGenerator.h"

float PerlinNoiseGenerator::getNoise(int x, int y) {
	float result = Maths::randomFloat(x * 49632 + y * 325176 + m_Seed) * 2.0f - 1.0f;
	return result;
}

float PerlinNoiseGenerator::getSmoothNoise(int x, int y) {
	float corners = (getNoise(x - 1, y - 1) + getNoise(x + 1, y - 1) + getNoise(x - 1, y + 1) + getNoise(x + 1, y + 1)) / 16.0f;
	float sides = (getNoise(x - 1, y) + getNoise(x + 1, y) + getNoise(x, y - 1) + getNoise(x, y + 1)) / 8.0f;
	float center = getNoise(x, y) / 4.0f;

	return corners + sides + center;
}

float PerlinNoiseGenerator::cosinInterpolate(float a, float b, float blend) {
	double theta = blend * M_PI;
	float f = (float)((1.0f - cos(theta)) * 0.5f);
	return a * (1 - f) + b * f;
}

float PerlinNoiseGenerator::getInterpolateNoise(float x, float y) {
	int intX = (int)x;
	float fragX = x - intX;
	int intY = (int)y;
	float fragY = y - intY;

	float v1 = getSmoothNoise(intX, intY);
	float v2 = getSmoothNoise(intX + 1, intY);
	float v3 = getSmoothNoise(intX, intY + 1);
	float v4 = getSmoothNoise(intX + 1, intY + 1);
	float i1 = cosinInterpolate(v1, v2, fragX);
	float i2 = cosinInterpolate(v3, v4, fragX);

	return cosinInterpolate(i1, i2, fragY);
}

float PerlinNoiseGenerator::getEdgeFactor(float x, float y) {
	float nearEdge = m_MaxSize * 0.1f;
	float farEdge = m_MaxSize - nearEdge;

	float xFactorNear = Maths::clamp(x / nearEdge, 0, 1);
	float xFactor = Maths::clamp(1.0f - (x - farEdge) / nearEdge, 0, xFactorNear);

	float yFactorNear = Maths::clamp(y / nearEdge, 0, xFactor);
	return Maths::clamp(1.0f - (y - farEdge) / nearEdge, 0, yFactorNear);
}

PerlinNoiseGenerator::PerlinNoiseGenerator(int seed, float smoothness, float size, float edgeHeight) {
	m_Seed = seed;
	m_Smoothness = smoothness;
	m_MaxSize = size;
	m_EdgeHeight = edgeHeight;
}

PerlinNoiseGenerator::PerlinNoiseGenerator(float smoothness, float size, float edgeHeight) {
	m_Seed = Maths::randomInt(1000000000);
	m_Smoothness = smoothness;
	m_MaxSize = size;
	m_EdgeHeight = edgeHeight;
}

float PerlinNoiseGenerator::getPerlinNoise(float x, float y) {
	float total = 0;
	float d = (float)pow(2, OCATAVES - 1);
	for (int i = 0; i < OCATAVES; i++) {
		float freq = (float)(pow(2, i) / d);
		float amp = (float)pow(ROUGHNESS, i) * AMPLITUDE;
		total += getInterpolateNoise(x * m_Smoothness * freq, y * m_Smoothness * freq) * amp;
	}
	//return total;
	float edgeFactor = getEdgeFactor(x, y);
	float result = total * edgeFactor + (1 - edgeFactor) * m_EdgeHeight;
	return result;
}

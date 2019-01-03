#include "SunCycle.h"

float SunCycle::STEEPNESS = 0.8f;
float SunCycle::DAY_BIAS = 0.65f;
float SunCycle::MIDNIGHT = 1.0f / 24.0f;
float SunCycle::MIN_LIGHT_HEIGHT = 0.37f;

void SunCycle::addSun() {
	//TODO:临时添加贴图
	Texture sunTexture = Texture::newTexture("res/lenseFlare/sun.png").noFiltering().clampEdges().create();
	m_sun = new Sun(
		ParticleTexture(sunTexture, 2, false),
		100,
		vec3(0, -1, 0)
	);
}

void SunCycle::update(float time) {
	double theta = (time - MIDNIGHT) * 2 * M_PI;
	//TODO:标记透视矩阵改动x,y取反
	m_lightSourcePos.x = -sin(theta);
	m_lightSourcePos.y = -cos(theta) * STEEPNESS + DAY_BIAS;
	m_lightSourcePos.z = cos(theta);

	vec3 sunDir = m_lightSourcePos;
	sunDir.negate();
	sunDir.y += 0.65f;
	sunDir.y /= 1.7f;
	sunDir.normalize();
	EnvironmentVariables::VISIBLE_SUN_DIR = sunDir;

	if (m_sun != NULL) {
		m_sun->update(sunDir);
	}

	float diff = MIN_LIGHT_HEIGHT - m_lightSourcePos.y;
	if (diff > 0) {
		m_lightSourcePos.y = MIN_LIGHT_HEIGHT + diff * 0.4f;
	}

	m_lightSourcePos.negate();
	m_lightSourcePos.normalize();

	EnvironmentVariables::setLightDirection(m_lightSourcePos);
}

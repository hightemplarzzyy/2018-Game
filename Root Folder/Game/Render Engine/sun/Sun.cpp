#include "Sun.h"
#include "cfloat"
#include "../../Source/main/CamerManager.h"

float Sun::DISTANCE = 20;

Sun::Sun(ParticleTexture texture, float scale, vec3 direction) :
	Particle(texture, vec3(), vec3(), 0, FLT_MAX, 0, scale) {
	m_offset = direction;
	m_offset.negate();
	m_offset.normalize();
	m_offset.scale(DISTANCE);
	setManualStage(true);
}

void Sun::update(vec3 direction) {
	m_offset = direction;
	m_offset.negate();
	m_offset.normalize();
	m_offset.scale(DISTANCE);
	setStages(0, 1, 1 - EnvironmentVariables::getSunEffectBrightness());
}

vec3 Sun::getPosition() {
	return m_offset + CameraManager::pcamera->getPosition();
}

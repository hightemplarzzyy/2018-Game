#include "FlareManager.h"

#include "../environment/environment.h"

float FlareManager::BRIGHTNESS = 0.5f;
float FlareManager::FIRST_SIZE = 0.4f;
float FlareManager::MIDDLE_SIZE = 0.07f;
float FlareManager::GAP = FIRST_SIZE - MIDDLE_SIZE;
float FlareManager::MAX_SCREEN_DIS = 0.6f;
vec2 FlareManager::CENTER_SCREEN = vec2(0.5f, 0.5f);

FlareManager::FlareManager(int middleIndex, std::vector<FlareTexture> flares) {
	m_middleIndex = middleIndex;
	m_flareTexture = flares;
	initCoords();
}

void FlareManager::doOcclusionTest() {
	m_render.doOcclusionTest(EnvironmentVariables::getSunScreenPosition());
}

void FlareManager::calculatePosition(vec2 toCenter, vec2 sunPos, vec3 & flareData) {
	toCenter.x *= flareData.z; 
	toCenter.y *= flareData.z;
	vec2 flarePosition = CENTER_SCREEN + toCenter;
	flareData.x = flarePosition.x;
	flareData.y = flarePosition.y;
}

void FlareManager::updateFlarePositions(vec2 toCenter, vec2 sunScreenCoords) {
	for (int i = 0; i < m_flareCoordinates.size(); i++) {
		calculatePosition(toCenter, sunScreenCoords, m_flareCoordinates[i]);
	}
}

void FlareManager::initCoords() {
	int count = m_flareTexture.size();
	m_flareCoordinates.resize(count);
	for (int i = 0; i < count; i++) {
		int absDifference = i - m_middleIndex;
		float sizeFactor = (float)absDifference / float(m_middleIndex);
		m_flareCoordinates[i] = vec3(0.0f, 0.0f, sizeFactor);
	}
}

void FlareManager::render(vec3 sunDirection) {
	vec2 * pSunCoords = EnvironmentVariables::getSunScreenPosition();
	if (pSunCoords == NULL) {
		return;
	}
	vec2 toCenter = CENTER_SCREEN - *pSunCoords;
	//TODO:光线较暗不便于显示暂时屏蔽
	//float brightness = 1 - (sqrt(toCenter.x * toCenter.x + toCenter.y * toCenter.y) / MAX_SCREEN_DIS);
	//float dirBrgihtness = EnvironmentVariables::getSunEffectBrightness();
	//brightness *= dirBrgihtness;
	float brightness = 1;
	if (brightness <= 0) {
		return;
	}
	updateFlarePositions(toCenter, *pSunCoords);
	m_render.render(m_flareTexture, m_flareCoordinates, brightness);
}

void FlareManager::cleanUp() {
	m_render.cleanUp();
}

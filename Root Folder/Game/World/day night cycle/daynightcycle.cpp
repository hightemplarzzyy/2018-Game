#include "DayNightCycle.h"

#include "../../basics/DIsplayManager.h"

float DayNightCycle::DARK = 0.25f;
float DayNightCycle::SOFT = 0.1f;

void DayNightCycle::addSun() {
	m_sunCycle.addSun();
}

void DayNightCycle::update() {
	float time = getTime();
	Color color = m_lightColorCycle.getColor(time);
	EnvironmentVariables::skyColour = m_horizonColorCycle.getColor(time);
	EnvironmentVariables::MIST_COL = m_mistCycle.getColor(time);
	EnvironmentVariables::horizonColour = m_skyColorCycle.getColor(time);
	EnvironmentVariables::setLightColor(color);
	updateMistAccount(time);
	calculateStarBrightness(time);
	updateShadowDarkness(time);
	m_sunCycle.update(time);
}

float DayNightCycle::getTime() {
	//TODO:gamemanage没有定义 暂时这么获取时间
	float time = DisplayManager::getTime();
	time /= 20;
	time = fmod(time, 1);
	return time;
}

void DayNightCycle::updateShadowDarkness(float time) {
	if (time > 12.0f / 24.0f && time < 15.0f / 24.0f) {
		EnvironmentVariables::SHADOW_DARKNESS = DARK;
	}
	else if (time > 21.0f / 24.0f || time < 3.0f / 24.0f) {
		EnvironmentVariables::SHADOW_DARKNESS = SOFT;
	}
	else if (time >= 3.0f / 24.0f && time <= 12.0f / 24.0f) {
		float blend = Maths::smoothStep(3.0f / 24.0f, 12.0f / 24.0f, time);
		EnvironmentVariables::SHADOW_DARKNESS = SOFT + (DARK - SOFT) * blend;
	}
	else if (time >= 15.0f / 24.0f && time <= 21.0f / 24.0f) {
		float blend = Maths::smoothStep(15.0f / 24.0f, 21.0f / 24.0f, time);
		EnvironmentVariables::SHADOW_DARKNESS = DARK + (SOFT - DARK) * blend;
	}
}

void DayNightCycle::updateMistAccount(float time) {
	float mistyness;
	if (time > 0.5f) {
		mistyness = Maths::smoothStep(15.0f / 24.0f, 18.0f / 24.0f, time);
	}
	else {
		mistyness = 1 - Maths::smoothStep(7.0f / 24.0f, 10.0f / 24.0f, time);
	}
	mistyness = 1 - mistyness;
	EnvironmentVariables::MIST_VALS.x = 15 + mistyness * 20;
	EnvironmentVariables::MIST_VALS.y = 75 + mistyness * 50;
}

void DayNightCycle::calculateStarBrightness(float time) {
	if (time > 0.5f) {
		EnvironmentVariables::starBrightness = Maths::smoothStep(22.0f / 24.0f, 24.0f / 24.0f, time);
	}
	else {
		EnvironmentVariables::starBrightness = 1 - Maths::smoothStep(3.0f / 24.0f, 5.0f / 24.0f, time);
	}
}
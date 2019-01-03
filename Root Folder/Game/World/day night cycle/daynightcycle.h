#pragma once

#include "suncycle.h"
#include "lightcolorcycle.h"
#include "horizoncolorcycle.h"
#include "mistcolorcycle.h"
#include "skycolorcycle.h"

class DayNightCycle {
private:
	SunCycle m_sunCycle;
	LightColorCycle m_lightColorCycle;
	SkyColorCycle m_skyColorCycle;
	HorizonColorCycle m_horizonColorCycle;
	MistColorCycle m_mistCycle;

	static float DARK;
	static float SOFT;

public:
	void addSun();
	void update();

private:
	float getTime();
	void updateShadowDarkness(float time) ;
	void updateMistAccount(float time) ;
	void calculateStarBrightness(float time) ;

};
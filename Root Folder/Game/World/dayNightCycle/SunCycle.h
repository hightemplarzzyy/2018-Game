#pragma once

#include "../../Render Engine/toolbox/maths/maths_func.h"
#include "../../Render Engine/sun/Sun.h"

class SunCycle {
private:
	static float STEEPNESS;
	static float DAY_BIAS;
	static float MIDNIGHT;
	static float MIN_LIGHT_HEIGHT;

	vec3 m_lightSourcePos;
	Sun * m_sun;

public:
	void addSun();
	void update(float time);

};

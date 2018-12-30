#pragma once

#include <vector>
#include "../toolbox/maths/vec2.h"
#include "FlareRender.h"

class FlareManager {
private:
	static float BRIGHTNESS;
	static float MAX_SCREEN_DIS;
	static vec2 CENTER_SCREEN;

public:
	static float FIRST_SIZE;
	static float MIDDLE_SIZE;
	static float GAP;

	std::vector<FlareTexture> m_flareTexture;
	int m_middleIndex;

	std::vector<vec3> m_flareCoordinates;
	FlareRender m_render;

public:
	FlareManager(int middleIndex, std::vector<FlareTexture> flares);

	void doOcclusionTest();
	void render(vec3 sunDirection);
	void cleanUp();

private:
	void initCoords();
	void updateFlarePositions(vec2 toCenter, vec2 sunScreenCoords);
	void calculatePosition(vec2 toCenter, vec2 sunPos, vec3 & flareData);

	


};
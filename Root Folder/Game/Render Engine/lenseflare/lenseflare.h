#pragma once

#include "../textures/texture.h"
#include "flaremanager.h"

class LenseFlare {
private:

	static int MIDDLE_INDEX;

	static Texture circleRings;
	static Texture smallGreen;
	static Texture rainbowRing;
	static Texture smallDot;
	static Texture sunStar;
	static Texture redDot;
	static Texture rainbow2;

	FlareManager * m_FlareManager;

private:
	static Texture loadTexture(const char * Path);

public:
	LenseFlare(mat4 projectionMartrix, mat4 viewMatrix);
	~LenseFlare();

	void render(vec3 lightDirection, bool sunVisible);
	void doOcclusionTest();
	void cleanUp();



	
};
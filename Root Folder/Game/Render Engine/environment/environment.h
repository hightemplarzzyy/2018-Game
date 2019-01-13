#ifndef _ENVIRONMENT_VARIABLES_H_
#define _ENVIRONMENT_VARIABLES_H_

#include "../toolbox/Color.h"

class EnvironmentVariables {
public:
	static float GRAVITY;
	static float starBrightness;

	static Color VOID_COLOUR;
	static Color horizonColour;
	static Color skyColour;
	static vec3 VISIBLE_SUN_DIR;
	static vec2 MIST_VALS;			//雾
	static Color MIST_COL;
	static float SHADOW_DARKNESS;

private:
	static float LARGE_NUMBER;
	static Color lightColor;
	static vec3 lightDirection;

	static float ambientWeighting;
	static float diffuseWeighting;

	static float skyRotateSpeed;
	static vec2 * sunScreenCoords;

public:

	static void update();

	static float getSunEffectBrightness();
	static Color getLightColor();
	static float getSkyRotateSpeed();
	static float getAmbientWeighting();
	static float getDiffuseWeighting();
	static vec3 getLightDirection();
	static void setLightColor(Color color);
	static void setLightDirection(vec3 lightDir);
	static vec2 * getSunScreenPosition();

private:
	static vec3 getSunPosition(vec3 sunDirection);
	static vec2 * getSunScreenCoords();



};


#endif // !_ENVIRONMENT_VARIABLES_H_




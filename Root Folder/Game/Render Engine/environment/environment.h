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
	static vec2 MIST_VALS;			//Он
	static Color MIST_COL;
	static float SHADOW_DARKNESS;

	static float LARGE_NUMBER;
	static Color lightColor;
	static vec3 lightDirection;

	static float ambientWeighting;
	static float diffuseWeighting;

	static float skyRotateSpeed;
	static vec2 sunScreenCoords;


};


#endif // !_ENVIRONMENT_VARIABLES_H_




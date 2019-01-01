#include "environment.h"

#include "../toolbox/maths/maths_func.h"


float EnvironmentVariables::GRAVITY				= -10.0f;
float EnvironmentVariables::starBrightness		= 0;
Color EnvironmentVariables::VOID_COLOUR			= Color(1.0f,0.87f,0.6f);
Color EnvironmentVariables::horizonColour		= Color(1.0f, 0.87f, 0.6f);
Color EnvironmentVariables::skyColour			= Color(0.6f, 0.9f, 1.0f);

//vec3 EnvironmentVariables::VISIBLE_SUN_DIR		= vec3(1.0f,-0.08f,0.5f);
vec3 EnvironmentVariables::VISIBLE_SUN_DIR		= vec3(0.0f, 0.5f, -0.5f);

vec2 EnvironmentVariables::MIST_VALS			= vec2(20,120);
Color EnvironmentVariables::MIST_COL			= Color(255, 220, 210, true);
float EnvironmentVariables::SHADOW_DARKNESS		= 0.2f;

float EnvironmentVariables::LARGE_NUMBER		= 1000000.0f;
Color EnvironmentVariables::lightColor			= Color(0.8f, 0.6f, 0.6f);
vec3 EnvironmentVariables::lightDirection		= vec3(0.4f, -1.0f, 0.2f);

float EnvironmentVariables::ambientWeighting	= 0.6f;
float EnvironmentVariables::diffuseWeighting	= 0.6f;

float EnvironmentVariables::skyRotateSpeed		= 1.0f;


vec2 * EnvironmentVariables::sunScreenCoords	= NULL;

void EnvironmentVariables::setLightColor(Color color) {
	lightColor = color;
}

void EnvironmentVariables::setLightDirection(vec3 lightDir) {
	lightDirection = lightDir;
}

vec3 EnvironmentVariables::getLightDirection() {
	return lightDirection;
}

Color EnvironmentVariables::getLightColor() {
	return lightColor;
}

float EnvironmentVariables::getAmbientWeighting() {
	return ambientWeighting;
}

float EnvironmentVariables::getDiffuseWeighting() {
	return diffuseWeighting;
}

float EnvironmentVariables::getSkyRotateSpeed() {
	return skyRotateSpeed;
}


//��ݾ��������ǿ��
float EnvironmentVariables::getSunEffectBrightness() {
	return 1 - Maths::smoothStep(0.0f, 0.2f, VISIBLE_SUN_DIR.y);
}

vec2 * EnvironmentVariables::getSunScreenPosition() {
	return sunScreenCoords;
}

vec3 EnvironmentVariables::getSunPosition(vec3 sunDirection) {
	sunDirection.negate();
	sunDirection.scale(LARGE_NUMBER);
	return sunDirection;
}

vec2 * EnvironmentVariables::getSunScreenCoords() {
	//TODO:����û����Ķ���view��project����
	vec3 * pScreenCoords = Maths::converToScreenSpace(getSunPosition(VISIBLE_SUN_DIR), mat4(1), mat4::perspective(45, 1.78, 0.1, 300));
//	vec3 * pScreenCoords = Maths::converToScreenSpace(getSunPosition(VISIBLE_SUN_DIR), mat4(1), mat4(1));
	if (pScreenCoords == NULL) {
		return NULL;
	}
	vec2 * pAns = new vec2(pScreenCoords->x, pScreenCoords->y);
	delete pScreenCoords;

	return pAns;
}

void EnvironmentVariables::update() {
	if (sunScreenCoords != NULL) {
		delete sunScreenCoords;
	}
	sunScreenCoords = getSunScreenCoords();
	//TODO:��ҹѭ��û��ʵ��
}



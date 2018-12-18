#include "environment.h"

float EnvironmentVariables::GRAVITY				= -10.0f;
float EnvironmentVariables::starBrightness		= 0;
Color EnvironmentVariables::VOID_COLOUR			= Color(1.0f,0.87f,0.6f);
Color EnvironmentVariables::horizonColour		= Color(1.0f, 0.87f, 0.6f);
Color EnvironmentVariables::skyColour			= Color(0.6f, 0.9f, 1.0f);
vec3 EnvironmentVariables::VISIBLE_SUN_DIR		= vec3(1.0f,-0.08f,0.5f);
vec2 EnvironmentVariables::MIST_VALS			= vec2(20,120);
Color EnvironmentVariables::MIST_COL			= Color(255, 220, 210, true);
float EnvironmentVariables::SHADOW_DARKNESS		= 0.2f;

float EnvironmentVariables::LARGE_NUMBER		= 1000000.0f;
Color EnvironmentVariables::lightColor			= Color(0.8f, 0.6f, 0.6f);
vec3 EnvironmentVariables::lightDirection		= vec3(0.4f, -1.0f, 0.2f);

float EnvironmentVariables::ambientWeighting	= 0.6f;
float EnvironmentVariables::diffuseWeighting	= 0.6f;

float EnvironmentVariables::skyRotateSpeed		= 1.0f;



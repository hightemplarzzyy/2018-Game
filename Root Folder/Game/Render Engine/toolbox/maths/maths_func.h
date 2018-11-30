#pragma once

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

class Maths {
public:
	static float getDistanceBetweenPoints(float x1, float y1, float x2, float y2) {
		float dx = x2 - x1;
		float dy = y2 - y1;
		return sqrt(dx * dx + dy * dy);
	}
};
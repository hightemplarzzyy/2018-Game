#pragma once

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

#define _USE_MATH_DEFINES
#include <math.h>

class Maths {
public:
	static float getDistanceBetweenPoints(float x1, float y1, float x2, float y2) {
		float dx = x2 - x1;
		float dy = y2 - y1;
		return sqrt(dx * dx + dy * dy);
	}

	//产生一个单位随机向量
	static vec3 generteRandomUnitVector() {
		float theta = float(rand() % 100) / 50 * M_PI;
		float z = float(rand() % 100) / 100;
		float rootOneMinusZSquared = sqrt(1 - z * z);
		float x = rootOneMinusZSquared * cos(theta);
		float y = rootOneMinusZSquared * sin(theta);
		return vec3(x, y, z);
	}

	//产生一个
	static vec3 randomPointOnCircle(const vec3 & normal, float radius) {
		vec3 randomPerpendicular; 
		do {
			vec3 randomVector = generteRandomUnitVector();
			randomPerpendicular = cross(randomVector, normal);
		} while (randomPerpendicular.lengthSquared() == 0);
		randomPerpendicular.normalize();
		//TODO:原函数操作有点迷
		float dis = float(rand() % 100) / 100;
		float factor = dis * radius;
		randomPerpendicular.scale(factor);


	}
};
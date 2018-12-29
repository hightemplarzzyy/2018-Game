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
		float theta = float(rand() % 100) / 50.0f * M_PI;
		float z = float(rand() % 100) / 100.0f;
		float rootOneMinusZSquared = sqrt(1 - z * z);
		float x = rootOneMinusZSquared * cos(theta);
		float y = rootOneMinusZSquared * sin(theta);
		return vec3(x, y, z);
	}


	//产生一个垂直于法线的圆上的向量
	static vec3 randomPointOnCircle(const vec3 & normal, float radius) {
		vec3 randomPerpendicular; 
		do {
			vec3 randomVector = generteRandomUnitVector();
			randomPerpendicular = cross(randomVector, normal);
		} while (randomPerpendicular.lengthSquared() == 0);
		randomPerpendicular.normalize();
		//TODO:原函数操作有点迷
		float dis = float(rand() % 100) / 100;
//		float dis = 1;
		float factor = dis * radius;
		randomPerpendicular.scale(factor);
		return randomPerpendicular;
	}

	//产生圆锥方向的向量
	static vec3 generateRandomUnitVectorWithinCone(vec3 coneDirection, float angle) {
		float cosAngle = cos(angle / 180.0f * M_PI);
		float theta = float(rand() % 100) / 50.0f * M_PI;
		float z = cosAngle + float(rand() % 100) / 100.0f * (1 - cosAngle);
		float rootOneMinusZSqured = sqrt(1 - z * z);
		float x = rootOneMinusZSqured * cos(theta);
		float y = rootOneMinusZSqured * sin(theta);

		vec4 direction = vec4(x, y, z, 1.0f);
		//如果coneDirection不是z轴
		if (coneDirection.x != 0 || coneDirection.y != 0 || 
			(coneDirection.z != 1 && coneDirection.z != -1)) {
			vec3 rotateAxis = cross(coneDirection, vec3(0, 0, 1));
			rotateAxis.normalize();
			float rotateAngle = acos(dot(coneDirection, vec3(0, 0, 1))) / M_PI * 180;
			mat4 rotationMatrix = mat4::rotation(-rotateAngle, rotateAxis);
			direction = direction * rotationMatrix;
		}
		else if (coneDirection.z == -1) {
			coneDirection.z = 1;
		}

		return vec3(direction.x, direction.y, direction.z);
	}
};
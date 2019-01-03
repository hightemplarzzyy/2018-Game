#pragma once

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>

class Maths {
public:

	static int randomInt(int nextInt) {
		srand((int)time(0));
		return rand() % nextInt;
	}

	static float randomFloat(int seed) {
		srand(seed);
		float m1 = (float)(rand() / float(RAND_MAX));
		return m1;
	}

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

	//记得delete创建的向量
	static vec3 * converToScreenSpace(vec3 position, mat4 viewMatrix, mat4 projMatrix) {
		vec4 coords = vec4(position.x, position.y, position.z, 1.0f);
		coords = coords * viewMatrix * projMatrix;
		return clipSpaceToScreenSpace(coords);
	}

	//记得delete创建的向量
	static vec3 * clipSpaceToScreenSpace(vec4 coords) {
		if (coords.w < 0) {
			return NULL;
		}
		return new vec3(
			((coords.x / coords.w) + 1) / 2.0f,
			1 - ((coords.y / coords.w) + 1) / 2.0f,
			coords.z);
	}

	static float clamp(float value, float min, float max) {
		float mid = value > min ? value : min;
		return mid < max ? mid : max;
	}

	static float smoothStep(float edge0, float edge1, float x) {
		float t = clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
		return t * t *(3.0f - 2.0f*t);
	}
};
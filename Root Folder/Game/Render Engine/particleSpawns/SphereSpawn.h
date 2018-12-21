#pragma once

#include "ParticleSpawn.h"
#include "../toolbox/maths/maths_func.h"

//球型粒子位置生成器
class SphereSpawn :public ParticleSpawn {
private:
	float m_radius;

public:
	SphereSpawn(float radius) :m_radius(radius) {

	}

	virtual vec4 getBaseSpawnPosition() {
		vec3 spherePoint = Maths::generteRandomUnitVector();
		//TODO:原函数操作有点迷
		float dis = float(rand() % 100) / 100;
		float factor = dis * m_radius;
		spherePoint.scale(factor);
		return vec4(spherePoint.x, spherePoint.y, spherePoint.z, 1.0f);
	}

};
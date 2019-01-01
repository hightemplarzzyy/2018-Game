#pragma once

#include "ParticleSpawn.h"

//点位置生成器
class PointSpawn : public ParticleSpawn {
public:
	PointSpawn() {

	}

	virtual vec4 getBaseSpawnPosition() {
		return vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
};
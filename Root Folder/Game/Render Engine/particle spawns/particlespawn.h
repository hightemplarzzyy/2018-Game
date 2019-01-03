#pragma once

#include "../toolbox/maths/vec4.h"

//粒子位置生成器
class ParticleSpawn {
public:
	virtual vec4 getBaseSpawnPosition() = 0;
};
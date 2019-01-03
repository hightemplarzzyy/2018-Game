#pragma once

#include "ParticleSpawn.h"

#include "../toolbox/maths/maths_func.h"

class CircleSpawn :public ParticleSpawn {
private:
	vec3 m_Heading;
	float m_Radius;

public:
	CircleSpawn(vec3 heading, float radius) :m_Heading(heading), m_Radius(radius) {

	}

	virtual vec4 getBaseSpawnPosition() {
		vec3 point = Maths::randomPointOnCircle(m_Heading, m_Radius);
		return vec4(point.x, point.y, point.z, 1.0f);
	}

};
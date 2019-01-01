#pragma once

#include "ParticleSpawn.h"

#include "../toolbox/maths/maths_func.h"

class CircleSpawn :public ParticleSpawn {
private:
	vec3 m_heading;
	float m_radius;

public:
	CircleSpawn(vec3 heading, float radius) :m_heading(heading), m_radius(radius) {

	}

	virtual vec4 getBaseSpawnPosition() {
		vec3 point = Maths::randomPointOnCircle(m_heading, m_radius);
		return vec4(point.x, point.y, point.z, 1.0f);
	}

};
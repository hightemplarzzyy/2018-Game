#pragma once

#include "particlespawn.h"
#include "../toolbox/maths/vec3.h"


class LineSpawn :public ParticleSpawn {
private:
	float m_Length;
	vec3 m_Axis;

public:
	LineSpawn(float length, vec3 axis) :m_Length(length), m_Axis(axis) {

	}

	virtual vec4 getBaseSpawnPosition() {
		float actualLenght = m_Length;
		vec3 actualAxis = vec3(
			m_Axis.x * actualLenght,
			m_Axis.y * actualLenght,
			m_Axis.z * actualLenght );
		actualAxis.scale(float(rand() % 200) / 200 - 0.5);
		return vec4(actualAxis.x, actualAxis.y, actualAxis.z, 1.0f);
	}

	
};
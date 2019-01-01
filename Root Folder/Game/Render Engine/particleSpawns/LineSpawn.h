#pragma once

#include "ParticleSpawn.h"
#include "../toolbox/maths/vec3.h"


class LineSpawn :public ParticleSpawn {
private:
	float m_length;
	vec3 m_axis;

public:
	LineSpawn(float length, vec3 axis) :m_length(length), m_axis(axis) {

	}

	virtual vec4 getBaseSpawnPosition() {
		float actualLenght = m_length;
		vec3 actualAxis = vec3(
			m_axis.x * actualLenght,
			m_axis.y * actualLenght,
			m_axis.z * actualLenght );
		actualAxis.scale(float(rand() % 200) / 200 - 0.5);
		return vec4(actualAxis.x, actualAxis.y, actualAxis.z, 1.0f);
	}

	
};
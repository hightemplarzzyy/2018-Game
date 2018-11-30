#pragma once

#include"uniform.h"
#include "../toolbox/maths/maths_func.h"

class UniformVec3 : public Uniform {

public:
	UniformVec3(std::string name) : Uniform(name) {};

	void load(vec3 v) {
		glUniform3f(m_Location, v.x, v.y, v.z);
		return;
	}
	void load(float x, float y, float z) {
		glUniform3f(m_Location, x, y, z);
		return;
	}
};
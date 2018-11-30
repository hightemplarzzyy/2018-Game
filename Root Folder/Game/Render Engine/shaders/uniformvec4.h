#pragma once

#include"uniform.h"
#include "../toolbox/maths/maths_func.h"

class UniformVec4 : public Uniform {

public:
	UniformVec4(std::string name) : Uniform(name) {};

	void load(vec4 v) {
		glUniform4f(m_Location, v.x, v.y, v.z, v.w);
		return;
	}
	void load(float x, float y, float z, float w) {
		glUniform4f(m_Location, x, y, z, w);
		return;
	}
};
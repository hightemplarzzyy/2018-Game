#pragma once

#include"uniform.h"
#include "../toolbox/maths/maths_func.h"

class UniformVec2 : public Uniform {

public:
	UniformVec2(std::string name) : Uniform(name) {};

	void load(vec2 v) {
		glUniform2f(m_Location, v.x, v.y);
		return;
	}
	void load(float x, float y) {
		glUniform2f(m_Location, x, y);
		return;
	}
};
#pragma once

#include"uniform.h"
#include "../toolbox/maths/maths_func.h"

class UniformBool : public Uniform {

public:
	UniformBool(std::string name) : Uniform(name) {};
	void load(bool b) {
		glUniform1i(m_Location, b ? 1 : 0);
		return;
	}
};
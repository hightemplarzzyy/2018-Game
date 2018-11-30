#pragma once

#include"uniform.h"
#include "../toolbox/maths/maths_func.h"

class Uniform1f : public Uniform {

public:
	Uniform1f(std::string name) : Uniform(name) {};
	void load(int f) {
		glUniform1i(m_Location, f);
		return;
	}
};
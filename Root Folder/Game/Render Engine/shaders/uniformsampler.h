#pragma once

#include"uniform.h"
#include "../toolbox/maths/maths_func.h"

class UniformSampler : public Uniform {

public:
	UniformSampler(std::string name) : Uniform(name) {};
	void load(int texUnit) {
		glUniform1i(m_Location, texUnit);
		return;
	}
};
#pragma once

#include"uniform.h"
#include "../toolbox/maths/maths_func.h"

class UniformMat4 : public Uniform {
	
public:
	UniformMat4(std::string name) : Uniform(name) {};
	void load(mat4 m) {
		glUniformMatrix4fv(m_Location, 1, GL_FALSE, m.elements);
		return;
	}
};
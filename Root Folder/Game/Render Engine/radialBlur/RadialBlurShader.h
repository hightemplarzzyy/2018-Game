#pragma once

#include "../shaders/shader.h"
#include "../shaders/uniformvec2.h"

class RadialBlurShader :public Shader {
public:
	UniformVec2 * lightPositionOnScreen = new UniformVec2("lightPositionOnScreen");

	RadialBlurShader(const char * vertexPath, const char * fragmentPath) :
		Shader(vertexPath, fragmentPath) {
		storeAllUniformLocation();
	}

	virtual void storeAllUniformLocation() {
		lightPositionOnScreen->storeLocation(m_ShaderID);
	}

};
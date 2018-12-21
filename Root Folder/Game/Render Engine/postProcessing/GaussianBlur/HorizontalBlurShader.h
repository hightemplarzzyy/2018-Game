#pragma once

#include "../../shaders/shader.h"
#include "../../shaders/uniform1f.h"

class HorizontalBlurShader :public Shader {
public:
	Uniform1f * width = new Uniform1f("width");

	HorizontalBlurShader(const char * vertexPath, const char * fragmentPath) :
		Shader(vertexPath, fragmentPath) {
		storeAllUniformLocation();
	}

	virtual void storeAllUniformLocation() {
		width->storeLocation(m_ShaderID);
	}
};
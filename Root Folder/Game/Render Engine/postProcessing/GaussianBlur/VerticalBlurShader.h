#pragma once

#include "../../shaders/shader.h"
#include "../../shaders/uniform1f.h"

class VerticalBlurShader :public Shader {
public:
	Uniform1f *height = new Uniform1f("height");

	VerticalBlurShader(const char * vertexPath, const char * fragmentPath) :
		Shader(vertexPath, fragmentPath) {
		storeAllUniformLocation();
	}

	virtual void storeAllUniformLocation() {
		height->storeLocation(m_ShaderID);
	}

};
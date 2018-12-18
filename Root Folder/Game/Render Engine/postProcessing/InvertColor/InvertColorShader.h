#pragma once

#include "../../shaders/shader.h"
#include "../../shaders/uniformvec2.h"

class InvertColorShader :public Shader {
public:
	InvertColorShader(const char* vertexPath, const char* fragmentPath) :Shader(vertexPath, fragmentPath) {
		storeAllUniformLocation();
	}

	virtual void storeAllUniformLocation() {

	}
};
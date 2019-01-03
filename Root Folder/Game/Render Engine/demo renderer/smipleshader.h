#pragma once

#include "../shaders/shader.h"
#include "../shaders/uniformmat4.h"
#include "../shaders/uniformvec2.h"

class SimpleShader : public Shader {
public:
	UniformMat4 *projection_matrix = new UniformMat4("projection_matrix");
	UniformMat4 *model_matrix = new UniformMat4("model_matrix");
	UniformMat4 *view_matrix = new UniformMat4("view_matrix");
	UniformVec2 *light_position = new UniformVec2("light_position");

	SimpleShader(const char* vertexPath, const char* fragmentPath) :Shader(vertexPath, fragmentPath) {
		storeAllUniformLocation();
	}
	virtual void storeAllUniformLocation() {
		projection_matrix->storeLocation(m_ShaderID);
		model_matrix->storeLocation(m_ShaderID);
		view_matrix->storeLocation(m_ShaderID);
		light_position->storeLocation(m_ShaderID);
		return;
	}
};
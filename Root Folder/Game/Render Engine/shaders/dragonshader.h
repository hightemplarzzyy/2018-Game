#pragma once

#include "shader.h"
#include "uniformvec3.h"
#include "uniformmat4.h"
#include "uniformsampler.h"

class DragonShader : public Shader {
public:
	UniformMat4 *projection_matrix = new UniformMat4("projection_matrix");
	UniformMat4 *model_matrix = new UniformMat4("model_matrix");
	UniformMat4 *view_matrix = new UniformMat4("view_matrix");
	UniformVec3 *light_position = new UniformVec3("light_position");
	//Texture Test
	UniformSampler *diff_map = new UniformSampler("diff_map");

	DragonShader(const char* vertexPath, const char* fragmentPath) :Shader(vertexPath, fragmentPath) {
		storeAllUniformLocation();
	}
	virtual void storeAllUniformLocation() {
		projection_matrix->storeLocation(m_ShaderID);
		model_matrix->storeLocation(m_ShaderID);
		view_matrix->storeLocation(m_ShaderID);
		light_position->storeLocation(m_ShaderID);
		diff_map->storeLocation(m_ShaderID);
		return;
	}
};
#pragma once

#include "../shaders/shader.h"
#include "../shaders/uniformvec3.h"
#include "../shaders/uniformvec4.h"
#include "../shaders/uniformmat4.h"

#include "../toolbox/maths/maths_func.h"

class TerrainShader :public Shader {
public:
	UniformMat4 * perspective = new UniformMat4("perspective_matrix");
	UniformMat4 * view = new UniformMat4("view_matrix");
	UniformMat4 * model = new UniformMat4("model_matrix");
	UniformVec3 * lightpos = new UniformVec3("lightPos");
	UniformVec4 * NowlightColor = new UniformVec4("NowlightColor");
	UniformVec3 * viewpos = new UniformVec3("viewPos");


	TerrainShader(const char* vertexPath, const char* fragmentPath) :Shader(vertexPath, fragmentPath) {
		storeAllUniformLocation();
	}
	virtual void storeAllUniformLocation() {
		perspective->storeLocation(m_ShaderID);
		view->storeLocation(m_ShaderID);
		lightpos->storeLocation(m_ShaderID);
		NowlightColor->storeLocation(m_ShaderID);
		viewpos->storeLocation(m_ShaderID);
		model->storeLocation(m_ShaderID);
		return;
	}
};
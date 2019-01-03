#pragma once

#include "..\shaders\shader.h"
#include "..\shaders\uniformmat4.h"
#include "..\shaders\uniformvec2.h"
#include "..\shaders\uniformvec3.h"

class TerrainShader : public Shader {
public:
	UniformMat4 *projectionMatrix = new UniformMat4("projection_matrix");
	UniformMat4 *viewMatrix = new UniformMat4("view_matrix");
	UniformVec3 *lightDirection = new UniformVec3("light_direction");
	UniformVec3 *lightColor = new UniformVec3("light_color");
	UniformVec2 *worldCenter = new UniformVec2("worldCenter");

public:
	TerrainShader();
	TerrainShader(const char *vertexPath, const char *fragmentPath);
	
	virtual void storeAllUniformLocation();
};
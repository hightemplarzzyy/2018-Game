#include "terrainShader.h"

TerrainShader::TerrainShader() : Shader("terrainVertex.glsl", "terrainFragment.glsl") {
	storeAllUniformLocation();
}

TerrainShader::TerrainShader(const char* vertexPath, const char* fragmentPath) : Shader(vertexPath, fragmentPath){
	storeAllUniformLocation();
}

void TerrainShader::storeAllUniformLocation() {
	projectionMatrix->storeLocation(m_ShaderID);
	viewMatrix->storeLocation(m_ShaderID);
	lightDirection->storeLocation(m_ShaderID);
	lightColor->storeLocation(m_ShaderID);
	worldCenter->storeLocation(m_ShaderID);
}

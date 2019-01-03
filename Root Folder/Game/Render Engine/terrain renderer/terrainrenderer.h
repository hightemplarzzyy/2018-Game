#pragma once
#include "terrainShader.h"
#include "..\..\World\terrain\terrain.h"

class TerrainRenderer {
public:
	TerrainShader *m_Shader;

public:
	
	TerrainRenderer(const char* vertexPath, const char* fragmentPath);
	void render(Terrain& terrain);
};
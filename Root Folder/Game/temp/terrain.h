#pragma once
#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <vector>

#include "../Render Engine/toolbox/maths/maths_func.h"
#include "../Render Engine/buffers/vertexarray.h"
#include "Perlin.h"


const vec3 LIGHT_GREEN = vec3(0.8, 1.0, 0.0);
const vec3 DEEP_GREEN = vec3(0.6, 0.8, 0.2);
const vec3 LAND = vec3(0.8, 0.4, 0.2);
const vec3 ICE = vec3(0.8, 1.0, 1.0);

class Terrain {
private:
	int m_mapWidth;
	int m_mapHeight;
	int m_size;

	float m_k;
	float m_gap;

	Perlin m_perlin;

	std::vector <vec3> m_map;
	std::vector <vec3> m_normals;
	std::vector <vec3> m_vertexes;
	std::vector <vec3> m_colors;

	VertexArray m_vao;
	

public:
	Terrain();
	Terrain(const int & mapWidth, const int & mapHeight);

	void Init(int octaves, int persistence);	//初始化点信息
	void GetColor(float height);				//根据高度生成颜色
	void Generate();							//生成片面计算法线
	void DataTrasnform(std::vector <vec3> & vertexes, std::vector <vec3> & normals, std::vector <vec3> & colors );

	void create();
	void render();

	inline void size();
};

#endif
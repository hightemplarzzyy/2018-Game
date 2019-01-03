#pragma once

#include <map>
#include "../../Render Engine/particles/particleTexture.h"

class ParticleAtlasCache {

public:
	//TODO:初始化放在loadALL里面需要先调用才能渲染色块粒子
	static Texture TRIANGLE;

	static std::map <int, ParticleTexture> particleTexture;

	static ParticleTexture getAtlas(int id);

	static void loadAtlas(int id, const char * path, int rows, bool additive);

	static void loadALL();
	
};
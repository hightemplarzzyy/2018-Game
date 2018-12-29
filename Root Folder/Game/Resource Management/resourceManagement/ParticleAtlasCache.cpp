#include "ParticleAtlasCache.h"


Texture ParticleAtlasCache::TRIANGLE;
std::map <int, ParticleTexture> ParticleAtlasCache::particleTexture;

ParticleTexture ParticleAtlasCache::getAtlas(int id) {
	return particleTexture[id];
}

void ParticleAtlasCache::loadAtlas(int id, const char * path, int rows, bool additive) {
	Texture texture = Texture::newTexture(path).clampEdges().create();
	ParticleTexture atlas = ParticleTexture(texture, rows, additive);
	particleTexture[id] = atlas;
}

void ParticleAtlasCache::loadALL() {

	TRIANGLE = Texture::newTexture("res/particleAtlases/triangle.png").clampEdges().create();
	loadAtlas(1, "res/particleAtlases/cosmic.png", 4, true);
	loadAtlas(2, "res/particleAtlases/blueHeal.png", 3, true);
	loadAtlas(3, "res/particleAtlases/diseased2.png", 2, false);
	loadAtlas(4, "res/particleAtlases/poison.png", 2, false);
	loadAtlas(5, "res/particleAtlases/pollen.png", 4, true);
	loadAtlas(6, "res/particleAtlases/snow.png", 4, true);
	loadAtlas(7, "res/particleAtlases/leaf.png", 2, false);
	loadAtlas(8, "res/particleAtlases/dust.png", 3, false);
	loadAtlas(9, "res/particleAtlases/rock.png", 2, false);
	loadAtlas(10, "res/particleAtlases/swamp.png", 2, false);
	loadAtlas(11, "res/particleAtlases/snore.png", 2, false);
	loadAtlas(12, "res/particleAtlases/floaty.png", 4, true);
	loadAtlas(13, "res/particleAtlases/fireFly.png", 2, true);
	loadAtlas(14, "res/particleAtlases/dusty.png", 3, false);
}
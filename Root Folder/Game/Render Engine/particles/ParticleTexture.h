#ifndef _PARTICLES_TEXTURE_H_
#define _PARTICLES_TEXTURE_H_

#include "../texture/Texture.h"

class ParticleTexture {
private:
	Texture m_texture;
	int m_numberOfRows;
	bool m_additive;
	bool m_glow = false;

public:
	ParticleTexture() {};
	ParticleTexture(Texture texture, int numberOfRows, bool additive) {};
	ParticleTexture(const ParticleTexture & pt) {};
	ParticleTexture setGlowy();

	bool operator < (const ParticleTexture & left) {
		return m_numberOfRows < left.m_numberOfRows;
	}

	friend bool operator < (const ParticleTexture & right, const ParticleTexture & left) {
		return right.m_numberOfRows < left.m_numberOfRows;
	}

	bool getGlows() {
		return m_glow;
	}

	int getTextureID() {
		return m_texture.getID();
	}
	int getNumberOfRows() {
		return m_numberOfRows;
	}
	bool isAdditive() {
		return m_additive;
	}
};

#endif // !_PARTICLES_TEXTURE_H_

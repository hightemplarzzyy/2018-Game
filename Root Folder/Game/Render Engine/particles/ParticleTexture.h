#ifndef _PARTICLES_TEXTURE_H_
#define _PARTICLES_TEXTURE_H_

#include "../textures/texture.h"

class ParticleTexture {
private:
	Texture m_texture;
	int m_numberOfRows;
	bool m_additive;
	bool m_glow = false;

public:
	//TODO:默认构造函数有一定风险
	ParticleTexture() = default;

	ParticleTexture(Texture texture, int numberOfRows, bool additive) {
		m_texture = texture;
		m_numberOfRows = numberOfRows;
		m_additive = additive;
	};

	ParticleTexture & setGlowy() {
		m_glow = true;
		return *this;
	}

	//为了能够放入MAP中
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

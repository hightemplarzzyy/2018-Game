#ifndef _PARTICLES_TEXTURE_H_
#define _PARTICLES_TEXTURE_H_

#include "../texture/Texture.h"

class ParticleTexture {
private:
	Texture m_texture;
	int m_numberOfRows;
	bool m_additive;
	bool glows = false;

public:
	ParticleTexture();
	ParticleTexture(Texture texture, int numberOfRows, bool additive);
	ParticleTexture(ParticleTexture & pt);

	ParticleTexture setGlowy();
	bool getGlows();
	int getTextureID();
	int getNumberOfRows() {
		return m_numberOfRows;
	}
	bool isAdditive();
};

#endif // !_PARTICLES_TEXTURE_H_

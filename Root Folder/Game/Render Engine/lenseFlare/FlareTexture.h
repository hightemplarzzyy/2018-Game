#pragma once

#include "../textures/texture.h"

class FlareTexture {

protected:
	Texture m_texture;
	float m_relativeScale;

public:
	FlareTexture(Texture texture) {
		m_texture = texture;
		m_relativeScale = 1;
	}

	FlareTexture(Texture texture, float relativeScale) {
		m_texture = texture;
		m_relativeScale = relativeScale;
	}

	bool isLoaded() {
		return m_texture.isLoaded();
	}

	int getID() {
		return m_texture.getID();
	}

	float getRelativeScale() {
		return m_relativeScale;
	}

};
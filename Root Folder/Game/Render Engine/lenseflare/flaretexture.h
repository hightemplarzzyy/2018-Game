#pragma once

#include "../textures/texture.h"

class FlareTexture {

protected:
	Texture m_Texture;
	float m_RelativeScale;

public:
	FlareTexture(Texture texture) {
		m_Texture = texture;
		m_RelativeScale = 1;
	}

	FlareTexture(Texture texture, float relativeScale) {
		m_Texture = texture;
		m_RelativeScale = relativeScale;
	}

	bool isLoaded() {
		return m_Texture.isLoaded();
	}

	int getID() {
		return m_Texture.getID();
	}

	float getRelativeScale() {
		return m_RelativeScale;
	}

};
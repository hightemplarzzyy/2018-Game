#pragma once

#include "../../Resource Management/gl request processing/glrequest.h"
#include "texturemanager.h"

class TextureDeleteRequest : public GlRequest
{
private:
	int m_TextureID;

public:
	TextureDeleteRequest(int textureID)
	{
		m_TextureID = textureID;
	}

	void executeGlRequest()
	{
		TextureManager::deleteTexture(m_TextureID);
	}
};
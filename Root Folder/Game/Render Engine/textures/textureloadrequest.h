#pragma once

#include "../../Resource Management/glRequestProcessing/glrequest.h"
#include "../../Resource Management/glRequestProcessing/glrequestprocessor.h"
#include "texture.h"
#include "texturemanager.h"

//TODO extend ResourceRequest
class TextureLoadRequest : public GlRequest 
{
public:
	Texture m_Texture;
	TextureBuilder m_Builder;
	TextureData m_Data;

public:
	TextureLoadRequest(Texture texture, TextureBuilder builder)
	{
		m_Texture = texture;
		m_Builder = builder;
	}

	void doResourceRequest()
	{
		m_Data = TextureManager::decodeTextureFile(m_Builder.getFile());
		GlRequestProcessor::sendRequest(*this);
	}

	void executeGlRequest() 
	{
		int texID = TextureManager::loadTextureToOpenGL(m_Data, m_Builder);
		m_Texture.setTextureID(texID);
	}
};
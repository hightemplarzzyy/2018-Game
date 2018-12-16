#include "texture.h"
#include "textureloadrequest.h"
#include "texturedeleterequest.h"

TextureBuilder TextureBuilder::clampEdges()
{
	m_ClampEdges = true;
	m_ClampToBorder = false;
	return *this;
}

TextureBuilder TextureBuilder::clampToBorder(float r, float g, float b, float a)
{
	m_BorderColour.x = r;
	m_BorderColour.y = g;
	m_BorderColour.z = b;
	m_BorderColour.w = a;
	m_ClampToBorder = true;
	m_ClampEdges = false;
	return *this;
}

TextureBuilder TextureBuilder::noMipMap()
{
	m_Mipmap = false;
	m_Anisotropic = false;
	return *this;
}

TextureBuilder TextureBuilder::nearestFiltering()
{
	m_Mipmap = false;
	m_Nearest = true;
	return *this;
}

TextureBuilder TextureBuilder::noFiltering()
{
	m_Anisotropic = false;
	return *this;
}

Texture TextureBuilder::create()
{
	Texture texture;
	TextureLoadRequest request = TextureLoadRequest(texture, *this);
	request.doResourceRequest();
	request.executeGlRequest();
	return request.m_Texture;
}

Texture::~Texture()
{
	m_Loaded = false;
	GlRequestProcessor::sendRequest(TextureDeleteRequest(m_TextureID));
}
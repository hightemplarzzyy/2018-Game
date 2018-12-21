#pragma once

#include "../../Resource Management/utils/fileutils.h"
#include "../toolbox/maths/maths_func.h"

//纹理数据类
class TextureData
{
private:
	int m_Width;
	int m_Height;
	unsigned char* m_Buffer;

public:
	TextureData() = default;

	TextureData(unsigned char* buffer, int width, int height)
	{
		m_Buffer = buffer;
		m_Width = width;
		m_Height = height;
	}

	int getWidth() const { return m_Width; }
	int getHeight() const { return m_Height; }
	unsigned char* getBuffer() const { return m_Buffer; }
};

class Texture;

//纹理配置器类
class TextureBuilder
{
private:
	bool m_ClampEdges;
	bool m_Mipmap;
	bool m_Anisotropic;
	bool m_Nearest;
	bool m_ClampToBorder;
	vec4 m_BorderColour;
	const char* m_File;

public:
	TextureBuilder() = default;

	TextureBuilder(const char* textureFile)
	{
		m_ClampEdges = false;
		m_Mipmap = true;
		m_Anisotropic = true;
		m_Nearest = false;
		m_ClampToBorder = false;
		m_File = textureFile;
		m_BorderColour = vec4(0, 0, 0, 0);
	}

	TextureBuilder clampEdges();
	TextureBuilder clampToBorder(float r, float g, float b, float a);
	TextureBuilder noMipMap();
	TextureBuilder nearestFiltering();
	TextureBuilder noFiltering();
	bool isClampEdges() const { return m_ClampEdges; }
	vec4 getBorderColour() const { return m_BorderColour; }
	bool isClampToBorder() const { return m_ClampToBorder; }
	bool isMipmap() const { return m_Mipmap; }
	bool isAnisotropic() const { return m_Anisotropic; }
	bool isNearest() const { return m_Nearest; }
	const char* getFile() const { return m_File; }

	/**
	* Creates a new texture, carries out the CPU loading, and loads to OpenGL.
	* @return The texture.
	*/
	Texture create();

	//TODO 在后台线程创建纹理
	//Texture createInBackground()
	//{
	//	Texture texture;
	//	RequestProcessor.sendRequest(new TextureLoadRequest(texture, this));
	//	return texture;
	//}

	////TODO 在主线程中创建纹理
	//Texture createInSecondThread() 
	//{
	//	Texture texture;
	//	TextureLoadRequest request = TextureLoadRequest(texture, *this);
	//	request.doResourceRequest();
	//	GlRequestProcessor::sendRequest(request);
	//	return texture;
	//}
};

class Texture 
{
private:
	bool m_Loaded = false;
	int m_TextureID;

public:
	Texture() { }

	void setTextureID(int id) 
	{
		m_TextureID = id;
		m_Loaded = true;
	}

	bool isLoaded()  { return m_Loaded; }
	int getID() { return m_TextureID; }

	~Texture();

	static TextureBuilder newTexture(const char* file) { return TextureBuilder(file); }

	static Texture getEmptyTexture() { return Texture(); }
};
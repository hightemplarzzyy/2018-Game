#pragma once

#include <GL/glew.h>
#include <stb_image.h>
#include <vector>
#include <string>
#include "texture.h"

class TextureManager 
{
private:
	static std::vector<GLuint> m_TextureCache;

public:
	static void cleanUp()
	{
		for (GLuint textureID : m_TextureCache)
		{
			glDeleteTextures(1, &textureID);
		}
	}

	static int loadCubeMapSameImage(const char* textureFile)
	{
		GLuint texID;
		glGenTextures(1, &texID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		TextureData data = decodeTextureFile(textureFile);
		for (int i = 0; i < 6; i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, data.getWidth(), data.getHeight(), 0,
				GL_BGRA, GL_UNSIGNED_BYTE, data.getBuffer());

		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		m_TextureCache.push_back(texID);
		return texID;
	}

	static TextureData decodeTextureFile(const char* file)
	{
		int width = 0;
		int height = 0;
		int mComponents;
		std::string pre = "Resource/";
		std::string res(file);
		unsigned char* data = stbi_load((pre + res).c_str(), &width, &height, &mComponents, 0);
		TextureData textureData(data, width, height);
		return textureData;
	}

	static int loadTextureToOpenGL(TextureData &data, TextureBuilder &builder)
	{
		GLuint texID;
		glGenTextures(1, &texID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		//unsigned char* d = *(data.getBuffer());
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data.getWidth(), data.getHeight(),
			0, GL_BGRA, GL_UNSIGNED_BYTE, data.getBuffer());

		if (builder.isMipmap())
		{
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			if (builder.isAnisotropic())
			{
				// TODO check supported
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0f);
			}
		}
		else if (builder.isNearest())
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}

		if (builder.isClampEdges())
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		else if (builder.isClampToBorder())
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			vec4 color = builder.getBorderColour();
			float borderColor[] = { color.x, color.y, color.z, color.w };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}

		stbi_image_free(data.getBuffer());
		m_TextureCache.push_back(texID);
		return texID;
	}

	static void deleteTexture(GLuint textureID)
	{
		auto iter = find(m_TextureCache.begin(), m_TextureCache.end(), textureID);
		if (m_TextureCache.end() != iter)
		{
			m_TextureCache.erase(iter);
			glDeleteTextures(1, &textureID);
		}
	}
};
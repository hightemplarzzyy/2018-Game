#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class WaterFrameBuffers 
{
protected:
	static int REFLECTION_WIDTH;
	static int REFRACTION_WIDTH;

private:
	static int REFLECTION_HEIGHT; 
	static int REFRACTION_HEIGHT;

public:
	unsigned int reflectionFrameBuffer;
	unsigned int reflectionTexture;
	unsigned int reflectionDepthBuffer;
	unsigned int refractionFrameBuffer;
	unsigned int refractionTexture;
	unsigned int refractionDepthTexture;

public:
	WaterFrameBuffers(){}

	void init();
	void cleanUp();
	inline void bindReflectionFrameBuffer()
	{
		bindFrameBuffer(reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
	}
	inline void bindRefractionFrameBuffer()
	{
		bindFrameBuffer(refractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT);
	}
	inline unsigned int getReflectionTexture()
	{
		return reflectionTexture;
	}
	inline unsigned int getRefractionDepthTexture()
	{
		return refractionDepthTexture;
	}

	void unbindCurrentFrameBuffer();

private:
	void initialiseReflectionFrameBuffer();
	void initialiseRefractionFrameBuffer();
	void bindFrameBuffer(int frameBuffer, int width, int height);
	unsigned int createFrameBuffer();
	int createTextureAttachment(int width, int height);
	int createDepthTextureAttachment(int width, int height);
	int createDepthBufferAttachment(int width, int height);
};
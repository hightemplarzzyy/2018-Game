#ifndef _FBO_BUILDER_H_
#define _FBO_BUILDER_H_

#include "Fbo.h"


//FBOµÄ¹¹½¨Æ÷
class FboBuilder {

public:

private:
	int m_width;
	int m_height;
	
	DepthBufferType m_depthBuffer	= NONE;
	bool m_clampEdege				= true;
	bool m_linearFilter				= true;
	bool m_colourBufer				= true;
	bool m_alphaChannel				= false;
	bool m_antialiased				= false;
	int  m_samples					= 1;

public:

	FboBuilder(int width, int height);
	FboBuilder & setDepthBuffer(DepthBufferType type);
	FboBuilder & repeatTexture();
	FboBuilder & antialias(int samples);
	FboBuilder & nearestFilter();
	FboBuilder & withAphaChannel(bool alpha);
	FboBuilder & noColourBuffer();
	Fbo * creat();
	
};

#endif // !_FBO_BUILDER_H_


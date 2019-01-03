#ifndef _FBO_H_
#define _FBO_H_

#include "../basics/DIsplayManager.h"

enum DepthBufferType {
	RENDER_BUFFER, TEXTURE, NONE
};

class Fbo {

private:

	int m_width;
	int m_height;

	bool m_alpha;

	GLuint m_frameBuffer;

	GLuint m_colourTexture;
	GLuint m_depthTexture;

	GLuint m_depthBuffer;
	GLuint m_colourBuffer;

	bool m_antiliased;

public:
	Fbo(int width, int height, DepthBufferType depthtype, bool useColourBuffer, bool linear,
		bool clamp, bool alpha, bool antialiased, int samples);

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	GLuint getColourTexture() { return m_colourTexture; };
	GLuint getDepthTexture() { return m_depthTexture; };

	void bindFrameBuffer();
	void unbindFrameBuffer();
	void bindToRead();
	void resolveMutisampledFbo(Fbo outputFbo);
	void blitToScreen();
	void initialiseFrameBuffer(DepthBufferType type, bool useColourBuffer,
		bool linear, bool clamp, int samples);
	void createTextureAttachment(bool linear, bool clamp);
	void createDepthTextureAttachment();
	void createDepthBufferAttachment(int samples);
	void createMutilisampleColourBuffer(int samples);
	void cleanUp();


};

#endif // !_FBO_H_

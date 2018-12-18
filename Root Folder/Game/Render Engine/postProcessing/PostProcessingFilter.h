#ifndef _POSTPROCESSING_FILTER_H_
#define _POSTPROCESSING_FILTER_H_


#include "../shaders/shader.h"
#include "../buffers/vertexarray.h"
#include "../basics/window.h"
#include "FboBuilder.h"

class PostProcessingFilter {
private:
	static float positions[8];
	static int VERTEX_COUNT;
	VertexArray m_vao;
	Shader * m_shader;
	Fbo * m_fbo;
	Window * m_window;

public:
	PostProcessingFilter(Shader * shader, int width, int heigh, bool alpha, Window * window);
	PostProcessingFilter(Shader * shader,Window * window);
	GLuint applyFilter(bool renderToScreen, std::vector<GLuint> inputTextures, Window * window);
	GLuint getOutputTexture();
	void blitToScreen();
	void cleanUp();
	virtual void prepareShader(Shader * shader);
	void prepare(bool renderToScreen, std::vector<GLuint> inputTextures);
	void finishRendering(bool renderToScreen);
};

#endif // !_POSTPROCESSING_FILTER_H_

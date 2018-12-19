#include "PostProcessingFilter.h"
#include "../toolbox/OpenglUtils.h"

float PostProcessingFilter::positions[8] = {
	-1, 1, -1, -1, 1, 1, 1, -1
};

int PostProcessingFilter::VERTEX_COUNT = 4;

PostProcessingFilter::PostProcessingFilter(Shader * shader, int width, int heigh, 
	bool alpha) {
	m_shader = shader;
	m_fbo = FboBuilder(width, heigh).withAphaChannel(alpha).setDepthBuffer(NONE).creat();
	m_vao.addBuffer(new Buffer(positions, 8, 2), 0);
}

PostProcessingFilter::PostProcessingFilter(Shader * shader) {
	m_shader = shader;
	m_fbo = FboBuilder(DisplayManager::getScreenWidth(), DisplayManager::getScreenHeigh()).creat();
	m_vao.addBuffer(new Buffer(positions, 8, 2), 0);
}

//inputTexture这个参数的问题
//有多个参数直接使用{ }放进去就好了 不用单独声明一个vector
GLuint PostProcessingFilter::applyFilter(bool renderToScreen, std::vector<GLuint> inputTextures) {
	prepare(renderToScreen, inputTextures);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, VERTEX_COUNT);
	finishRendering(renderToScreen);
	return m_fbo->getColourTexture();
}

void PostProcessingFilter::prepare(bool renderToScreen, std::vector<GLuint> inputTextures) {
	if (!renderToScreen) {//如果不需要显示到屏幕上
		m_fbo->bindFrameBuffer();
	}
	OpenglUtils::prepareNewRenderPass(Color(1.0f, 1.0f, 1.0f));
	m_shader->enable();
	OpenglUtils::antialias(false);
	OpenglUtils::disabaleDepthTesting();
	m_vao.bind();
	for (int i = 0; i < inputTextures.size(); i++) {
		OpenglUtils::bindTextureToBank(inputTextures[i], i);
	}
	prepareShader(m_shader);
}

void PostProcessingFilter::finishRendering(bool renderToScreen) {
	m_vao.unbind();
	m_shader->disable();
	OpenglUtils::disabaleBlending();
	OpenglUtils::enableDepthTesting();
	if (!renderToScreen) {
		m_fbo->unbindFrameBuffer();
	}
}

void PostProcessingFilter::prepareShader(Shader * shader) {

}

void PostProcessingFilter::blitToScreen() {
	m_fbo->blitToScreen();
}

GLuint PostProcessingFilter::getOutputTexture() {
	return m_fbo->getColourTexture();
}

void PostProcessingFilter::cleanUp() {
	m_fbo->cleanUp();
}
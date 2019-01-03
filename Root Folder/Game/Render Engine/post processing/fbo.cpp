#include "Fbo.h"


Fbo::Fbo(int width, int height,DepthBufferType depthtype, bool useColourBuffer, 
	bool linear, bool clamp, bool alpha, bool antialiased, int samples) {
	m_width = width;
	m_height = height;
	m_alpha = alpha;
	m_antiliased = antialiased;
	initialiseFrameBuffer(depthtype, useColourBuffer, linear, clamp, samples);
}

void Fbo::initialiseFrameBuffer(DepthBufferType type, bool useColourBuffer,
	bool linear, bool clamp, int samples) {

	//创建帧缓冲
	glGenFramebuffers(1, &m_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	//决定哪个颜色缓存将被绘制
	glDrawBuffer(useColourBuffer ? GL_COLOR_ATTACHMENT0 : GL_NONE);

	//创建各种附件
	if (!m_antiliased) {//不需要抗狗牙
		if (useColourBuffer) {
			createTextureAttachment(linear, clamp);
		}
		if (type == RENDER_BUFFER) {
			createDepthBufferAttachment(samples);
		}
		else if (type == TEXTURE) {
			createDepthTextureAttachment();
		}
	}
	else {
		createMutilisampleColourBuffer(samples);
		createDepthBufferAttachment(samples);
	}
	unbindFrameBuffer();
}
 

void Fbo::bindFrameBuffer() {

	//激活纹理
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

	glViewport(0, 0, m_width, m_height);

}

void Fbo::unbindFrameBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	glViewport(0, 0, DisplayManager::getScreenWidth(), DisplayManager::getScreenHeigh());
}

void Fbo::bindToRead() {
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_frameBuffer);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
}

//创建纹理附件
void Fbo::createTextureAttachment(bool linear, bool clamp) {

	glGenTextures(1, &m_colourTexture);
	glBindTexture(GL_TEXTURE_2D, m_colourTexture);

	//创建针缓冲纹理
	glTexImage2D(GL_TEXTURE_2D, 0, m_alpha ? GL_RGBA8 : GL_RGB8, m_width, m_height, 0,
		m_alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	//设定纹理超出边界时候的操作
	//GL_CLAMP_TO_EDGE 坐标会被截断到[0,1]之间。结果是坐标值大的被截断到纹理的边缘部分
	//GL_REPEAT 重复纹理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clamp ? GL_CLAMP_TO_EDGE : GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clamp ? GL_CLAMP_TO_EDGE : GL_REPEAT);
	//滤波操作，放大缩小
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, linear ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, linear ? GL_LINEAR : GL_NEAREST);
	
	//添加到缓冲区
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colourTexture, 0);
}

//创建深度缓冲附件
//samples采样值
void Fbo::createDepthBufferAttachment(int samples) {

	glGenRenderbuffers(1, &m_depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);

	if (m_antiliased) {//需要抗狗牙
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH_COMPONENT24, m_width, m_height);
	}
	else {
		//只分配内存没有填充
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_width, m_height);
	}

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);
}

//创建深度纹理附件
void Fbo::createDepthTextureAttachment() {

	glGenTextures(1, &m_depthTexture);
	glBindTexture(GL_TEXTURE_2D, m_depthTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_width, m_height, 0,
		GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);
}

//创建多重采样颜色缓冲
void Fbo::createMutilisampleColourBuffer(int samples) {

	glGenRenderbuffers(1, &m_colourBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_colourBuffer);

	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, m_alpha ? GL_RGBA8 : GL_RGB8, m_width, m_height);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colourBuffer);

}

void Fbo::resolveMutisampledFbo(Fbo outputFbo) {

	//GL_DRAW_FRAMEBUFFER 能够执行渲染，清空和其他写操作
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, outputFbo.m_frameBuffer);
	//GL_DRAW_FRAMEBUFFER 能够执行所有读操作
	glBindRenderbuffer(GL_READ_FRAMEBUFFER, m_frameBuffer);

	//将读缓冲的数据写入绘制缓冲中
	glBlitFramebuffer(0, 0, m_width, m_height,
		0, 0, outputFbo.m_width, outputFbo.m_height,
		GL_COLOR_BUFFER_BIT | GL_DEPTH_BITS, GL_NEAREST);

	unbindFrameBuffer();
}



void Fbo::blitToScreen() {

	//GL_DRAW_FRAMEBUFFER 能够执行渲染，清空和其他写操作
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glDrawBuffer(GL_BACK);
	//GL_DRAW_FRAMEBUFFER 能够执行所有读操作
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_frameBuffer);

	//将读缓冲的数据写入绘制缓冲中
	glBlitFramebuffer(0, 0, m_width, m_height,
		0, 0, DisplayManager::getScreenWidth(), DisplayManager::getScreenHeigh(),
		GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void Fbo::cleanUp() {
	glDeleteFramebuffers(1, &m_frameBuffer);
	glDeleteTextures(1, &m_colourTexture);
	glDeleteTextures(1, &m_depthTexture);
	glDeleteRenderbuffers(1, &m_depthBuffer);
	glDeleteRenderbuffers(1, &m_colourBuffer);
}
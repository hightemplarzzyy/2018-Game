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

	//����֡����
	glGenFramebuffers(1, &m_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	//�����ĸ���ɫ���潫������
	glDrawBuffer(useColourBuffer ? GL_COLOR_ATTACHMENT0 : GL_NONE);

	//�������ָ���
	if (!m_antiliased) {//����Ҫ������
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

	//��������
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

//����������
void Fbo::createTextureAttachment(bool linear, bool clamp) {

	glGenTextures(1, &m_colourTexture);
	glBindTexture(GL_TEXTURE_2D, m_colourTexture);

	//�����뻺������
	glTexImage2D(GL_TEXTURE_2D, 0, m_alpha ? GL_RGBA8 : GL_RGB8, m_width, m_height, 0,
		m_alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	//�趨�������߽�ʱ��Ĳ���
	//GL_CLAMP_TO_EDGE ����ᱻ�ضϵ�[0,1]֮�䡣���������ֵ��ı��ضϵ�����ı�Ե����
	//GL_REPEAT �ظ�����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clamp ? GL_CLAMP_TO_EDGE : GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clamp ? GL_CLAMP_TO_EDGE : GL_REPEAT);
	//�˲��������Ŵ���С
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, linear ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, linear ? GL_LINEAR : GL_NEAREST);
	
	//��ӵ�������
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colourTexture, 0);
}

//������Ȼ��帽��
//samples����ֵ
void Fbo::createDepthBufferAttachment(int samples) {

	glGenRenderbuffers(1, &m_depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);

	if (m_antiliased) {//��Ҫ������
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH_COMPONENT24, m_width, m_height);
	}
	else {
		//ֻ�����ڴ�û�����
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_width, m_height);
	}

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);
}

//�������������
void Fbo::createDepthTextureAttachment() {

	glGenTextures(1, &m_depthTexture);
	glBindTexture(GL_TEXTURE_2D, m_depthTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_width, m_height, 0,
		GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);
}

//�������ز�����ɫ����
void Fbo::createMutilisampleColourBuffer(int samples) {

	glGenRenderbuffers(1, &m_colourBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_colourBuffer);

	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, m_alpha ? GL_RGBA8 : GL_RGB8, m_width, m_height);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colourBuffer);

}

void Fbo::resolveMutisampledFbo(Fbo outputFbo) {

	//GL_DRAW_FRAMEBUFFER �ܹ�ִ����Ⱦ����պ�����д����
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, outputFbo.m_frameBuffer);
	//GL_DRAW_FRAMEBUFFER �ܹ�ִ�����ж�����
	glBindRenderbuffer(GL_READ_FRAMEBUFFER, m_frameBuffer);

	//�������������д����ƻ�����
	glBlitFramebuffer(0, 0, m_width, m_height,
		0, 0, outputFbo.m_width, outputFbo.m_height,
		GL_COLOR_BUFFER_BIT | GL_DEPTH_BITS, GL_NEAREST);

	unbindFrameBuffer();
}



void Fbo::blitToScreen() {

	//GL_DRAW_FRAMEBUFFER �ܹ�ִ����Ⱦ����պ�����д����
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glDrawBuffer(GL_BACK);
	//GL_DRAW_FRAMEBUFFER �ܹ�ִ�����ж�����
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_frameBuffer);

	//�������������д����ƻ�����
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
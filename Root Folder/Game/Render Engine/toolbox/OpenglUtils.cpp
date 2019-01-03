#include "OpenglUtils.h"

#include <GL/glew.h>

bool OpenglUtils::cullingBackFace	= false;
bool OpenglUtils::inWireFrame		= false;
bool OpenglUtils::isAlphaBlending	= false;
bool OpenglUtils::additiveBlending	= false;
bool OpenglUtils::antialiasing		= false;
bool OpenglUtils::scissorTest		= false;
int OpenglUtils::scissorBounds[4];

//为新的渲染做准备
void OpenglUtils::prepareNewRenderPass(Color skyColour) {
	prepareNewRenderPass(skyColour, 1);
}

//为新的渲染做准备，重置背景颜色
void OpenglUtils::prepareNewRenderPass(Color skyColour, float alpha) {
	glClearColor(skyColour.m_RGB.x, skyColour.m_RGB.y, skyColour.m_RGB.z, alpha);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	disabaleBlending();
	cullBackFaces(true);
	enableDepthTesting();
}

void OpenglUtils::prepareNewRenderParse(Color skyColour, float alpha) {
	glClearColor(skyColour.m_RGB.x, skyColour.m_RGB.y, skyColour.m_RGB.z, alpha);
	//清除深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	disabaleBlending();
	cullBackFaces(true);
	enableDepthTesting();
}


void OpenglUtils::prepareNewRenderPassOnlyDepth() {
	glClear(GL_DEPTH_BITS);
	disabaleBlending();
	cullBackFaces(true);
	enableDepthTesting();
}

void OpenglUtils::enableScissorTest(int x, int y, int width, int heigh) {
	if (!scissorTest) {
		scissorTest = true;
		glEnable(GL_SCISSOR_TEST);
	}

	if (x != scissorBounds[0] || y != scissorBounds[1]
		|| width != scissorBounds[2] || heigh != scissorBounds[3]) {
		glScissor(x, y, width, heigh);
		scissorBounds[0] = x;
		scissorBounds[1] = y;
		scissorBounds[2] = width;
		scissorBounds[3] = heigh;
	}
}

void OpenglUtils::disableScissorTest() {
	if (scissorTest) {
		scissorTest = false;
		glDisable(GL_SCISSOR_TEST);
	}
}

void OpenglUtils::antialias(bool enable) {
	//TODO：显示选项没有制作
	//if (!GraphicsOptions.ANTI_ALIASING) {
	//	return;
	//}
	if (enable && !antialiasing) {
		glEnable(GL_MULTISAMPLE);
		antialiasing = true;
	}
	else if(!enable && antialiasing){
		glDisable(GL_MULTISAMPLE);
		antialiasing = false;
	}
}

void OpenglUtils::enableAphaBlending() {
	if (!isAlphaBlending) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		isAlphaBlending = true;
		additiveBlending = false;
	}
}

void OpenglUtils::enableAdditiveBleding() {
	if (!additiveBlending) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		additiveBlending = true;
		isAlphaBlending = false;
	}
}

void OpenglUtils::disabaleBlending() {
	if (isAlphaBlending || additiveBlending) {
		glDisable(GL_BLEND);
		isAlphaBlending = false;
		additiveBlending = false;
	}
}

void OpenglUtils::enableDepthTesting() {
	glEnable(GL_DEPTH_TEST);
}

void OpenglUtils::disabaleDepthTesting() {
	glDisable(GL_DEPTH_TEST);
}

void OpenglUtils::cullBackFaces(bool cull) {
	if (cull & !cullingBackFace) {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		cullingBackFace = true;
	}
	else if (!cull & cullingBackFace) {
		glDisable(GL_CULL_FACE);
		cullingBackFace = false;
	}
}

void OpenglUtils::setWireFrame(bool goWireFrame) {
	if (goWireFrame && !inWireFrame) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		inWireFrame = true;
	}
	else if (!goWireFrame && inWireFrame) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		inWireFrame = false;
	}
}

void OpenglUtils::bindTextureToBank(GLuint textureID, int bankID) {
	glActiveTexture(GL_TEXTURE0 + bankID);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void OpenglUtils::bindTextureToBank(GLuint textureID, int bankID, int lodBias) {
	glActiveTexture(GL_TEXTURE0 + bankID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, lodBias);
	glActiveTexture(0);
}
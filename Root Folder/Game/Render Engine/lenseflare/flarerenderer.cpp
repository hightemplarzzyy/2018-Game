#include "flarerenderer.h"
#include "../basics/DIsplayManager.h"
#include "../toolbox/OpenglUtils.h"
#include <cmath>

float FlareRenderer::POSITIONS[] = { 0, 0, 0, 1, 1, 0, 1, 1 };
float FlareRenderer::TEST_BOX_WIDTH = 0.04f;
float FlareRenderer::TEST_BOX_HEIGHT;
float FlareRenderer::TOTAL_SAMPLES;


FlareRenderer::FlareRenderer() {

	TEST_BOX_HEIGHT = TEST_BOX_WIDTH * float(
		DisplayManager::getScreenWidth()) / float(DisplayManager::getScreenHeigh());
	TOTAL_SAMPLES = pow(TEST_BOX_WIDTH * DisplayManager::getScreenWidth(), 2) * 4.0f;

	m_Query = new Query(GL_SAMPLES_PASSED);
	m_Shader = new GuiShader("Render Engine/guiRendering/gui.vert", "Render Engine/guiRendering/gui.frag");
	m_Vao.addBuffer(new Buffer(POSITIONS, 8, 2), 0);
	initShader();
}

FlareRenderer::~FlareRenderer() {
	delete m_Query;
	delete m_Shader;
}

void FlareRenderer::initShader() {
	m_Shader->enable();
	m_Shader->overrideColor->load(vec3(1.0f, 1.0f, 1.0f));
	m_Shader->useOverrideColor->load(false);
	m_Shader->flipTexture->load(false);
	m_Shader->alpha->load(1.0f);
	m_Shader->disable();
}

void FlareRenderer::render(std::vector<FlareTexture> & flares, std::vector<vec3> & data, float brightness){
	prepare(brightness);
	m_Shader->alpha->load(brightness * m_Coverage);
	for (int i = 0; i < flares.size(); i++) {
		renderFlare(flares[i], data[i]);
	}
	endRendering();
}

void FlareRenderer::prepare(float brightness) {
	OpenglUtils::antialias(false);
	OpenglUtils::enableAdditiveBleding();
	OpenglUtils::disabaleDepthTesting();
	m_Shader->enable();
	m_Vao.bind();
}

void FlareRenderer::endRendering() {
	m_Vao.unbind();
	m_Shader->disable();
	OpenglUtils::disabaleBlending();
	OpenglUtils::enableDepthTesting();
}

void FlareRenderer::renderFlare(FlareTexture & flare, vec3 & data) {
	if (!flare.isLoaded()) {
		return;
	}
	OpenglUtils::bindTextureToBank(flare.getID(), 0);
	float scale = getActualSize(data.z) * flare.getRelativeScale();
	float yScale = scale * DisplayManager::getAspectRatio();
	vec4 t = vec4(data.x - scale / 2, data.y - yScale / 2, scale, yScale);
	m_Shader->transform->load(vec4(data.x - scale / 2, data.y - yScale / 2, scale, yScale));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void FlareRenderer::doOcclusionTest(vec2 * pvec2) {
	if (pvec2 == NULL) {
		m_Coverage = 0;
		return;
	}
	OpenglUtils::antialias(false);
	m_Shader->enable();
	m_Vao.bind();
	OpenglUtils::enableDepthTesting();
	glDepthMask(false);
	glColorMask(false, false, false, false);
	OpenglUtils::bindTextureToBank(0, 0);
	m_Shader->transform->load(
		vec4(pvec2->x - TEST_BOX_WIDTH / 2, pvec2->y - TEST_BOX_HEIGHT / 2,
			TEST_BOX_WIDTH, TEST_BOX_HEIGHT));

	if (m_Query->isResultReady()) {
		int result = m_Query->getResult();
		m_Coverage = min(result / TOTAL_SAMPLES, 1.0f);
	}
	if (!m_Query->isInUse()) {
		m_Query->start();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		m_Query->end();
	}
	glDepthMask(true);
	glColorMask(true, true, true, true);
	m_Vao.unbind();
	m_Shader->disable();
}

void FlareRenderer::cleanUp() {
	m_Query->delte();
}

float FlareRenderer::getActualSize(float sizeFactor) {
	//TODO:消除了再FlareManage里面的引用修改值的时候记得一并修改
	float middle_size = 0.07f;
	float first_size = 0.4f;
	float gap = first_size - middle_size;
	return middle_size + gap * abs(sizeFactor);
}
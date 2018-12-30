#include "FlareRender.h"
#include "../basics/DIsplayManager.h"
#include "../toolbox/OpenglUtils.h"
#include <cmath>

float FlareRender::POSITIONS[] = { 0, 0, 0, 1, 1, 0, 1, 1 };
float FlareRender::TEST_BOX_WIDTH = 0.04f;
float FlareRender::TEST_BOX_HEIGHT;
float FlareRender::TOTAL_SAMPLES;


FlareRender::FlareRender() {

	TEST_BOX_HEIGHT = TEST_BOX_WIDTH * float(
		DisplayManager::getScreenWidth()) / float(DisplayManager::getScreenHeigh());
	TOTAL_SAMPLES = pow(TEST_BOX_WIDTH * DisplayManager::getScreenWidth(), 2) * 4.0f;

	m_query = new Query(GL_SAMPLES_PASSED);
	m_shader = new GuiShader("Render Engine/guiRendering/gui.vert", "Render Engine/guiRendering/gui.frag");
	m_vao.addBuffer(new Buffer(POSITIONS, 8, 2), 0);
	initShader();
}

FlareRender::~FlareRender() {
	delete m_query;
	delete m_shader;
}

void FlareRender::initShader() {
	m_shader->enable();
	m_shader->overrideColor->load(vec3(1.0f, 1.0f, 1.0f));
	m_shader->useOverrideColor->load(false);
	m_shader->flipTexture->load(false);
	m_shader->alpha->load(1.0f);
	m_shader->disable();
}

void FlareRender::render(std::vector<FlareTexture> & flares, std::vector<vec3> & data, float brightness){
	prepare(brightness);
	m_shader->alpha->load(brightness * m_coverage);
	for (int i = 0; i < flares.size(); i++) {
		renderFlare(flares[i], data[i]);
	}
	endRendering();
}

void FlareRender::prepare(float brightness) {
	OpenglUtils::antialias(false);
	OpenglUtils::enableAdditiveBleding();
	OpenglUtils::disabaleDepthTesting();
	m_shader->enable();
	m_vao.bind();
}

void FlareRender::endRendering() {
	m_vao.unbind();
	m_shader->disable();
	OpenglUtils::disabaleBlending();
	OpenglUtils::enableDepthTesting();
}

void FlareRender::renderFlare(FlareTexture & flare, vec3 & data) {
	if (!flare.isLoaded()) {
		return;
	}
	OpenglUtils::bindTextureToBank(flare.getID(), 0);
	float scale = getActualSize(data.z) * flare.getRelativeScale();
	float yScale = scale * DisplayManager::getAspectRatio();
	vec4 t = vec4(data.x - scale / 2, data.y - yScale / 2, scale, yScale);
	m_shader->transform->load(vec4(data.x - scale / 2, data.y - yScale / 2, scale, yScale));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void FlareRender::doOcclusionTest(vec2 * pvec2) {
	if (pvec2 == NULL) {
		m_coverage = 0;
		return;
	}
	OpenglUtils::antialias(false);
	m_shader->enable();
	m_vao.bind();
	OpenglUtils::enableDepthTesting();
	glDepthMask(false);
	glColorMask(false, false, false, false);
	OpenglUtils::bindTextureToBank(0, 0);
	m_shader->transform->load(
		vec4(pvec2->x - TEST_BOX_WIDTH / 2, pvec2->y - TEST_BOX_HEIGHT / 2,
			TEST_BOX_WIDTH, TEST_BOX_HEIGHT));

	if (m_query->isResultReady()) {
		int result = m_query->getResult();
		m_coverage = min(result / TOTAL_SAMPLES, 1.0f);
	}
	if (!m_query->isInUse()) {
		m_query->start();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		m_query->end();
	}
	glDepthMask(true);
	glColorMask(true, true, true, true);
	m_vao.unbind();
	m_shader->disable();
}

void FlareRender::cleanUp() {
	m_query->delte();
}

float FlareRender::getActualSize(float sizeFactor) {
	//TODO:消除了再FlareManage里面的引用修改值的时候记得一并修改
	float middle_size = 0.07f;
	float first_size = 0.4f;
	float gap = first_size - middle_size;
	return middle_size + gap * abs(sizeFactor);
}
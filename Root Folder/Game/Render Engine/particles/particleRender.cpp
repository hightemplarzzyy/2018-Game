#include "particleRender.h"
#include "../environment/environment.h"

int ParticleRender::MAX_PARTICLES = 10000;
int ParticleRender::INSTANCE_DATA_SIZE = 21;
GLfloat ParticleRender::vertices[8] = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f };


ParticleRender::ParticleRender(const mat4 & projectionMatrix) {
	//添加材质贴图顶点
	m_vao.addBuffer(new Buffer(&vertices[0], 8, 2), 1);
	initShaders(projectionMatrix);
}

void ParticleRender::initShaders(const mat4 & projectionMatrix) {

	m_shader.enable();
	m_shader.projection_matrix->load(projectionMatrix);
	m_shader.disable();

	m_colourShader.enable();
	m_colourShader.projection_matrix->load(projectionMatrix);
	m_colourShader.disable();

}

void ParticleRender::bindTexture(ParticleTexture texture) {
	bindTexture(texture.getTextureID(), texture.isAdditive(), texture.getGlows());
	m_shader.numberOfRaws->load(texture.getNumberOfRows());
}

void ParticleRender::bindTexture(int textureId, bool additive, bool glow) {
	if (additive) {//需要混淆颜色
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		m_shader.light_colour->load(m_lightGlowColour);
	}
	else {
		if (glow) {
			m_shader.light_colour->load(m_lightGlowColour);
		}
		else {
			m_shader.light_colour->load(m_lightColour);
		}
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void ParticleRender::updateModelViewMatrix(Particle partice, mat4 viewMatrix, float * data) {
	mat4 modelMatrix = mat4::translation(partice.getPosition());

	//TODO：意义不明,暂且保留
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int p1 = i * 4 + j;
			int p2 = j * 4 + i;
			modelMatrix.elements[p1] = viewMatrix.elements[p2];
		}
	}

	mat4 modelViewMatrix = viewMatrix * modelMatrix;
	modelViewMatrix *= mat4::rotation(partice.getRotation(), vec3(0.0f, 0.0f, 1.0f));
	modelViewMatrix *= mat4::rotation(partice.getRotX(), vec3(0.0f, 1.0f, 0.0f));
	float scale = partice.getScale();
	modelViewMatrix *= mat4::scale(vec3(scale, scale, scale));

	for (int i = 0; i < 16; i++) {
		data[i + m_point++] = modelViewMatrix.elements[i];
	}
}

void ParticleRender::updateTexCoordInfo(Particle particle, float* data) {
	data[m_point++] = particle.getTexOffset1().x;
	data[m_point++] = particle.getTexOffset1().y;
	data[m_point++] = particle.getTexOffset2().x;
	data[m_point++] = particle.getTexOffset2().y;
	data[m_point++] = particle.getBlend();
}

void ParticleRender::updateColourCoordInfo(Particle particle, float* data) {
	data[m_point++] = particle.getTexOffset1().x;
	data[m_point++] = particle.getTexOffset1().y;
	data[m_point++] = particle.getTexOffset2().x;
	data[m_point++] = particle.getTexOffset2().y;
	data[m_point++] = 1;
}

void ParticleRender::renderTexturedParticles(ParticleTexture texture,
	std::map<ParticleTexture, std::vector<Particle>> particles, mat4 viewMatrix) {

	std::vector <Particle> particleList = particles[texture];
	bindTexture(texture);

	//所有粒子的信息放在缓存中
	GLfloat * buf = new GLfloat[particleList.size() * INSTANCE_DATA_SIZE];

	m_point = 0;
	for (int i = 0; i < particleList.size(); i++) {
		updateModelViewMatrix(particleList[i], viewMatrix, buf);
		updateTexCoordInfo(particleList[i], buf);
	}

	std::vector<int> textureFormate = { 4,4,4,4,4,1 };
	m_vao.addInterLeavedBuffer(new Buffer(buf, particleList.size() * INSTANCE_DATA_SIZE, 4)
		, 1, textureFormate);

	m_vao.bind();
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, particleList.size());
	m_vao.unbind();
}

void ParticleRender::renderColourParticles(std::vector<Particle> colourParticles,
	mat4 viewMatrix, bool additive) {
	if (additive) {
		m_colourShader.light_colour->load(m_lightGlowColour);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}
	else {
		m_colourShader.light_colour->load(m_lightColour);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	//所有粒子的信息放在缓存中
	GLfloat * buf = new GLfloat[colourParticles .size() * INSTANCE_DATA_SIZE];

	m_point = 0;
	for (int i = 0; i < colourParticles.size(); i++) {
		updateModelViewMatrix(colourParticles[i],viewMatrix, buf);
		updateColourCoordInfo(colourParticles[i], buf);
		buf[m_point++] = colourParticles[i].getTransparency();
	}

	std::vector <int> colourFormate = { 4,4,4,4,4,1,1 };
	m_vao.addInterLeavedBuffer(new Buffer(buf, colourParticles.size() * INSTANCE_DATA_SIZE, 4), 1,colourFormate);
	
	m_vao.bind();
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, colourParticles.size());
	m_vao.unbind();
}

void ParticleRender::calculateLightingFactor() {

	vec3 lightDir = EnvironmentVariables::lightDirection;

	float brightness = 0 > -lightDir.y ? 0 : -lightDir.y;

	vec3 diffuse = EnvironmentVariables::lightColor.getColor();

	float factor = EnvironmentVariables::diffuseWeighting * brightness;
	diffuse.x *= factor;
	diffuse.y *= factor;
	diffuse.z *= factor;

	vec3 ambient = EnvironmentVariables::lightColor.getColor();
	ambient.x *= EnvironmentVariables::ambientWeighting;
	ambient.y *= EnvironmentVariables::ambientWeighting;
	ambient.z *= EnvironmentVariables::ambientWeighting;

	m_lightColour = diffuse + ambient;
}

void ParticleRender::prepare() {
	//TODO:背面消隐,再ToolBox里面，没添加
	glEnable(GL_BLEND);
	glDepthMask(false);
	calculateLightingFactor();
}

void ParticleRender::finishRendering() {
	glDepthMask(true);
	//TODO:背面消隐,再ToolBox里面，没添加
	glDisable(GL_BLEND);
}

void ParticleRender::render(std::map<ParticleTexture, std::vector<Particle>> particles,
	std::vector<Particle> colourParticles, std::vector<Particle> additiveColourParticles, Camera camera) {

	mat4 viewMatrix = camera.CreateViewMatrix();
	
	prepare();

	m_shader.enable();
	std::map<ParticleTexture, std::vector<Particle>>::iterator it;
	for (it = particles.begin(); it != particles.end(); it++) {
		renderTexturedParticles(it->first, particles, viewMatrix);
	}
	m_shader.disable();

	m_colourShader.enable();
	glActiveTexture(GL_TEXTURE0);
	//TODO:加载三角形贴图
	//glBindTexture()
	renderColourParticles(colourParticles, viewMatrix, false);
	renderColourParticles(additiveColourParticles, viewMatrix, true);
	m_colourShader.disable();

	finishRendering();
}
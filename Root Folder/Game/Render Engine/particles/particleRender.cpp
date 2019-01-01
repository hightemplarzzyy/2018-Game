#include "particleRender.h"
#include "../environment/environment.h"
#include "../../Resource Management/resourceManagement/ParticleAtlasCache.h"

#include <ostream>

int ParticleRender::MAX_PARTICLES = 10000;
int ParticleRender::INSTANCE_DATA_SIZE = 21;
GLfloat ParticleRender::vertices[8] = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f };


ParticleRender::ParticleRender(const mat4 & projectionMatrix) {
	//添加材质贴图顶点
	m_vao = new VertexArray;
	m_vao->addBuffer(new Buffer(&vertices[0], 8, 2), 0);
	initShaders(projectionMatrix);
}

void ParticleRender::initShaders(const mat4 & projectionMatrix) {
	
	m_shader = new ParticleShader("Render Engine/particles/particle.vert", "Render Engine/particles/particle.frag");

	m_shader->enable();
	m_shader->projection_matrix->load(projectionMatrix);
	m_shader->disable();

	m_colourShader = new ParticleColourShader("Render Engine/particles/particleColour.vert", "Render Engine/particles/particleColour.frag");
	
	m_colourShader->enable();
	m_colourShader->projection_matrix->load(projectionMatrix);
	m_colourShader->disable();

}

void ParticleRender::bindTexture(ParticleTexture & texture) {
	bindTexture(texture.getTextureID(), texture.isAdditive(), texture.getGlows());

	m_shader->numberOfRaws->load(float(texture.getNumberOfRows()));
}

void ParticleRender::bindTexture(int textureId, bool additive, bool glow) {
	if (additive) {//需要混淆颜色
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		m_shader->light_colour->load(m_lightGlowColour);
	}
	else {
		if (glow) {
			m_shader->light_colour->load(m_lightGlowColour);
		}
		else {
			m_shader->light_colour->load(m_lightColour);
		}
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
}


void ParticleRender::renderTexturedParticles(ParticleTexture & texture,
	std::map<ParticleTexture, std::vector<Particle>> & particles, mat4 & viewMatrix) {

	//std::vector <Particle> particleList = particles[texture];

	bindTexture(texture);

	//所有粒子的信息放在缓存中
	std::vector <GLfloat> buf;
	buf.resize(particles[texture].size() * INSTANCE_DATA_SIZE);

	m_point = 0;
	for (int i = 0; i < particles[texture].size(); i++) {

		//传入矩阵
		mat4 model = mat4::translation(vec3(particles[texture][i].getPosition()));
		float scaleSize = particles[texture][i].getScale();
		model *= mat4::scale(vec3(scaleSize, scaleSize, scaleSize));
		//TODO:这里没有乘view矩阵 因为在着色器里面有一个
		model *= mat4::rotation(particles[texture][i].getRotation(), vec3(0, 0, 1));
		model *= mat4::rotation(particles[texture][i].getRotX(), vec3(0, 1, 0));
		for (int j = 0; j < 16; j++) {
			buf[m_point++] = model.elements[j];
		}

		//传入偏移坐标
		vec2 offset1 = particles[texture][i].getTexOffset1();
		vec2 offset2 = particles[texture][i].getTexOffset2();

		buf[m_point++] = offset1.x;
		buf[m_point++] = offset1.y;
		buf[m_point++] = offset2.x;
		buf[m_point++] = offset2.y;

		//传入混合值
		buf[m_point++] = particles[texture][i].getBlend();
	}

	//绑定数据格式
	std::vector<int> textureFormate = { 4,4,4,4,4,1 };
	m_vao->addInterLeavedBuffer(new Buffer(&buf[0], particles[texture].size() * INSTANCE_DATA_SIZE, 4), 1, textureFormate);
	m_shader->numberOfRaws->load(float(texture.getNumberOfRows()));


	//绘制粒子
	m_vao->bind();
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, particles[texture].size());
	m_vao->unbind();
}

void ParticleRender::renderColourParticles(std::vector<Particle> & colourParticles,
	mat4 & viewMatrix, bool additive) {
	if (additive) {
		m_colourShader->light_colour->load(m_lightGlowColour);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}
	else {
		m_colourShader->light_colour->load(m_lightColour);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	//所有粒子的信息放在缓存中
	std::vector <GLfloat> buf;
	buf.resize(colourParticles.size() * INSTANCE_DATA_SIZE);

	m_point = 0;
	for (int i = 0; i < colourParticles.size(); i++) {
		//传入矩阵
		mat4 model = mat4::translation(vec3(colourParticles[i].getPosition()));
		float scaleSize = colourParticles[i].getScale();
		model *= mat4::scale(vec3(scaleSize, scaleSize, scaleSize));
		//TODO:这里没有乘view矩阵 因为在着色器里面有一个
		model *= mat4::rotation(colourParticles[i].getRotation(), vec3(0, 0, 1));
		model *= mat4::rotation(colourParticles[i].getRotX(), vec3(0, 1, 0));
		for (int j = 0; j < 16; j++) {
			buf[m_point++] = model.elements[j];
		}

		//传入颜色
		Color color = colourParticles[i].getColour();
		//printf("%f %f %f\n", color.getR(), color.getG(), color.getB());
		buf[m_point++] = color.getR();
		buf[m_point++] = color.getG();
		buf[m_point++] = color.getB();
		buf[m_point++] = 1;
		
		//传入混合值
		buf[m_point++] = colourParticles[i].getTransparency();

	}

	std::vector <int> colourFormate = { 4,4,4,4,4,1 };
	m_vao->addInterLeavedBuffer(new Buffer(&buf[0], colourParticles.size() * INSTANCE_DATA_SIZE, 4), 1,colourFormate);
	
	m_vao->bind();
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, colourParticles.size());
	m_vao->unbind();
}

void ParticleRender::calculateLightingFactor() {

	vec3 lightDir = EnvironmentVariables::getLightDirection();

	float brightness = 0 > -lightDir.y ? 0 : -lightDir.y;

	vec3 diffuse = EnvironmentVariables::getLightColor().getColor();
	float factor = EnvironmentVariables::getDiffuseWeighting() * brightness;
	diffuse.scale(factor);

	vec3 ambient = EnvironmentVariables::getLightColor().getColor();
	ambient.scale(EnvironmentVariables::getAmbientWeighting());


	m_lightColour = diffuse + ambient;
}

void ParticleRender::prepare() {
	m_vao->bind();
	OpenglUtils::cullBackFaces(false);
	glEnable(GL_BLEND);
	glDepthMask(false);
	calculateLightingFactor();
}

void ParticleRender::finishRendering() {
	glDepthMask(true);
	OpenglUtils::cullBackFaces(true);
	glDisable(GL_BLEND);
	m_vao->unbind();
}

void ParticleRender::render(std::map<ParticleTexture, std::vector<Particle>> & particles,
	std::vector<Particle> & colourParticles, std::vector<Particle> & additiveColourParticles, Camera & camera) {

	mat4 viewMatrix = camera.CreateViewMatrix();

	prepare();

	m_shader->enable();

	std::map<ParticleTexture, std::vector<Particle>>::iterator it;
	for (it = particles.begin(); it != particles.end(); it++) {
		//TODO:有粒子不能更新的风险
		ParticleTexture temp = it->first;
		renderTexturedParticles(temp, particles, viewMatrix);
	}

	m_shader->disable();

	m_colourShader->enable();
	glActiveTexture(GL_TEXTURE0);
  
	glBindTexture(GL_TEXTURE_2D, ParticleAtlasCache::TRIANGLE.getID());
	if (colourParticles.size() != 0) {
		renderColourParticles(colourParticles, viewMatrix, false);
	}
	if (additiveColourParticles.size() != 0) {
		renderColourParticles(additiveColourParticles, viewMatrix, true);
	}

	m_colourShader->disable();

	finishRendering();
}


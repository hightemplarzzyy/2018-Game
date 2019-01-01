#ifndef _PARTICLES_RENDER_H_
#define _PARTICLES_RENDER_H_

#include <map>
#include <vector>

#include "../buffers/vertexarray.h"

#include "particle.h"
#include "particleShader.h"
#include "particleColourShader.h"
#include "ParticleTexture.h"
#include "../toolbox/OpenglUtils.h"


class ParticleRender {
private:
	static int MAX_PARTICLES;
	static int INSTANCE_DATA_SIZE;//记录世界矩阵，偏移量，透明度的数据长度 4*4+4+1
	static float vertices[8];

	int m_point = 0;
	
	VertexArray * m_vao;

	ParticleShader * m_shader;
	ParticleColourShader * m_colourShader;

	vec3 m_lightColour;
	vec3 m_lightGlowColour = vec3(1.0f, 1.0f, 1.0f);

public:
	ParticleRender() {};
	ParticleRender(const mat4 & projectionMatrix);

	void render(std::map<ParticleTexture, std::vector<Particle>> & particles,
		std::vector<Particle> &colourParticles, std::vector<Particle> &additiveColourParticles,
		Camera &camera);


	//TODO:临时渲染函数
	void render(std::map<ParticleTexture, std::vector<Particle>> & particles, Camera & camera) {

		prepare();

		m_shader->enable();
		std::map<ParticleTexture, std::vector<Particle>>::iterator it;
		for (it = particles.begin(); it != particles.end(); it++) {
			ParticleTexture temp = it->first;
			//TODO:不应该这里更新的，但是管理粒子的还没写，暂时顶替，演示用
			for (int i = 0; i < it->second.size(); i++) {
				it->second[i].update(camera);
			}
			mat4 view = camera.CreateViewMatrix();
			renderTexturedParticles(temp, particles, view);
		}
		m_shader->disable();

		finishRendering();
	}
	
private:
	void initShaders(const mat4 & projectionMatrix);
	void calculateLightingFactor();
	void renderTexturedParticles(ParticleTexture & texture, std::map<ParticleTexture, std::vector<Particle>> &particles,
		mat4 & viewMatrix);
	void renderColourParticles(std::vector<Particle> &colourParticles,
		mat4 & viewMatrix, bool additive);
	void bindTexture(ParticleTexture & texture);
	void bindTexture(int textureId, bool additive, bool glow);
	void prepare();
	void finishRendering();
	
};

#endif // !_PARTICLES_RENDER_H_

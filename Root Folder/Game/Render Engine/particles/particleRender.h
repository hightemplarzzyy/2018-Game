#ifndef _PARTICLES_RENDER_H_
#define _PARTICLES_RENDER_H_

#include <map>
#include <vector>

#include "particleShader.h"
#include "particleColourShader.h"
#include "particle.h"
#include "ParticleTexture.h"


class ParticleRender {
private:
	static int MAX_PARTICLES;
	static float vertices[8];
	static int INSTANCE_DATA_SIZE;
	
	ParticleShader m_shader;
	ParticleColourShader m_colourShader;

	vec3 m_lightPosition;
	vec3 m_lightGlow = vec3(1.0f, 1.0f, 1.0f);

	int m_pointer = 0;

public:
	ParticleRender(mat4 projectionMatrix);
	void render(std::map<ParticleTexture, std::vector<Particle>> particles,
		std::vector<Particle> colourParticles, std::vector<Particle> additiveColourParticles,
		Camera camera);
	void cleanUp();
	
private:
	void calculateLightingFactor();
	void renderTexturedParticles(ParticleTexture texture, std::map<ParticleTexture, std::vector<Particle>> particles,
		mat4 viewMatrix);
	void renderTexturedParticles(std::vector<Particle> colourParticles,
		mat4 viewMatrix, bool additive);
	void updateTexCoordInfo(Particle particle, float* data);
	void updateColourInfo(Particle particle, float* data);
	void bindTexture(ParticleTexture texture);
	void initShaders(mat4 projectionMatrix);
	void bindTexture(int textureId, bool additive, bool glows);
	void updateModelViewMatrix(Particle partice, mat4 viewMatrix, float * vboData);
	void storeMatrixData(mat4 matrix, float * data);
	void prepare();
	void finishRendering();
	
};

#endif // !_PARTICLES_RENDER_H_

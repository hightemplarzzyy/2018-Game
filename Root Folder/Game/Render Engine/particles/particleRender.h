#ifndef _PARTICLES_RENDER_H_
#define _PARTICLES_RENDER_H_

#include <map>
#include <vector>

#include "../buffers/vertexarray.h"

#include "particle.h"
#include "particleshader.h"
#include "particlecolorshader.h"
#include "particletexture.h"
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

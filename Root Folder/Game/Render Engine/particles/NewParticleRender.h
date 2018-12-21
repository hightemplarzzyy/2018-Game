#pragma once
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


class NewParticleRender {
private:
	static int MAX_PARTICLES;
	static int INSTANCE_DATA_SIZE;//记录世界矩阵，偏移量，透明度的数据长度 4*4+4+1
	static float vertices[8];

	int m_point = 0;

	VertexArray * m_vao;

	ParticleShader * m_shader;

	vec3 m_lightColour;
	vec3 m_lightGlowColour = vec3(1.0f, 1.0f, 1.0f);

public:
	
	NewParticleRender(const mat4 & projectionMatrix) {
		m_shader = new ParticleShader("Render Engine/particles/particle.vert", "Render Engine/particles/particle.frag");

		m_shader->enable();
		m_shader->projection_matrix->load(projectionMatrix);
		m_shader->numberOfRaws->load(4);
		m_shader->disable();

		m_vao = new VertexArray;
		m_vao->addBuffer(new Buffer(&vertices[0], 8, 2), 0);

	}

	void render(std::map<ParticleTexture, std::vector<Particle>> & particles, Camera & camera) {
		

		std::map<ParticleTexture, std::vector<Particle>> ::iterator it;
		for (it = particles.begin(); it != particles.end(); it++) {
			std::vector <GLfloat> buffer;
			buffer.clear();
			buffer.resize(it->second.size() * INSTANCE_DATA_SIZE);
			int p = 0;
			for (int i = 0; i < it->second.size(); i++) {
				it->second[i].update(camera);
				mat4 model = mat4::translation(it->second[i].getPosition());
				float scaleSize = it->second[i].getScale();
				model *= mat4::scale(vec3(scaleSize, scaleSize, scaleSize));
				for (int j = 0; j < 16; j++) {
					buffer[p++] = model.elements[j];
				}
				vec2 offset1 = it->second[i].getTexOffset1();
				vec2 offset2 = it->second[i].getTexOffset2();
				buffer[p++] = offset1.x;
				buffer[p++] = offset1.y;
				buffer[p++] = offset2.x;
				buffer[p++] = offset2.y;
				buffer[p++] = it->second[i].getBlend();
			}
			Buffer * pbuf = new Buffer(&buffer[0], it->second.size() * INSTANCE_DATA_SIZE, 4);
			m_vao->addInterLeavedBuffer(pbuf, 1, { 4,4,4,4,4,1 });
			delete pbuf;

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, it->first.getTextureID());

			m_shader->enable();
			m_shader->light_colour->load(m_lightGlowColour);
			m_vao->bind();
			glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, it->second.size());
			m_vao->unbind();
			m_shader->disable();
			glDisable(GL_BLEND);
		}

		
	}

private:
	

};

int NewParticleRender::MAX_PARTICLES = 100000;
int NewParticleRender::INSTANCE_DATA_SIZE = 21;
float NewParticleRender::vertices[8] = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f };

#endif // !_PARTICLES_RENDER_H_

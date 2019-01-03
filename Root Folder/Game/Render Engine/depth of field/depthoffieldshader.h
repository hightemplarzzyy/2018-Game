#pragma once

#include "../shaders/shader.h"
#include "../shaders/uniformsampler.h"
#include "../shaders/uniform1f.h"

class DepthOfFieldShader :public Shader {
public:
	UniformSampler * m_OriginalTexture = new UniformSampler("originalTexture");
	UniformSampler * m_BlurredTexture = new UniformSampler("blurredTexture");
	UniformSampler * m_DepthTexture = new UniformSampler("depthTexture");
	Uniform1f * m_AimDistance = new Uniform1f("aimDistance");

	DepthOfFieldShader(const char * vertexPath, const char * fragmentPath) :
		Shader(vertexPath, fragmentPath) {
		storeAllUniformLocation();

		enable();
		m_OriginalTexture->load(0);
		m_BlurredTexture->load(1);
		m_DepthTexture->load(2);
		disable();
	}

	virtual void storeAllUniformLocation() {
		m_OriginalTexture->storeLocation(m_ShaderID);
		m_BlurredTexture->storeLocation(m_ShaderID);
		m_DepthTexture->storeLocation(m_ShaderID);
		m_AimDistance->storeLocation(m_ShaderID);
	}
};
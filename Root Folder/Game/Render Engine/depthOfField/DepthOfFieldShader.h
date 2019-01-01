#pragma once

#include "../shaders/shader.h"
#include "../shaders/uniformsampler.h"
#include "../shaders/uniform1f.h"

class DepthOfFieldShader :public Shader {
public:
	UniformSampler * originalTexture = new UniformSampler("originalTexture");
	UniformSampler * blurredTexture = new UniformSampler("blurredTexture");
	UniformSampler * depthTexture = new UniformSampler("depthTexture");
	Uniform1f * aimDistance = new Uniform1f("aimDistance");

	DepthOfFieldShader(const char * vertexPath, const char * fragmentPath) :
		Shader(vertexPath, fragmentPath) {
		storeAllUniformLocation();

		enable();
		originalTexture->load(0);
		blurredTexture->load(1);
		depthTexture->load(2);
		disable();
	}

	virtual void storeAllUniformLocation() {
		originalTexture->storeLocation(m_ShaderID);
		blurredTexture->storeLocation(m_ShaderID);
		depthTexture->storeLocation(m_ShaderID);
		aimDistance->storeLocation(m_ShaderID);
	}
};
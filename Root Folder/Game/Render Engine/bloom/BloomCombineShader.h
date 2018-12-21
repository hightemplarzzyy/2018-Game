#ifndef _BLOOM_COMBINE_SHADER_H_
#define _BLOOM_COMBINE_SHADER_H_

#include "../shaders/shader.h"
#include "../shaders/uniformsampler.h"

class BloomCombineShader :public Shader {
public:
	UniformSampler * originalTexture = new UniformSampler("originalTexture");
	UniformSampler * blurredTexture = new UniformSampler("bloomTexture");

	BloomCombineShader(const char * vertexPath, const char * fragmentPath) :
		Shader(vertexPath, fragmentPath) {
		storeAllUniformLocation();
	}

	virtual void storeAllUniformLocation() {
		originalTexture->storeLocation(m_ShaderID);
		blurredTexture->storeLocation(m_ShaderID);
	}
	
};

#endif // !_BLOOM_COMBINE_SHADER_H_

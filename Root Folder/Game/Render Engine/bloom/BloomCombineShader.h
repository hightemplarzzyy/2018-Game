#ifndef _BLOOM_COMBINE_SHADER_H_
#define _BLOOM_COMBINE_SHADER_H_

#include "../shaders/shader.h"
#include "../shaders/uniformsampler.h"

class BloomCombineShader :public Shader {
public:
	UniformSampler * m_OriginalTexture = new UniformSampler("originalTexture");
	UniformSampler * m_BlurredTexture = new UniformSampler("bloomTexture");

	BloomCombineShader(const char * vertexPath, const char * fragmentPath) :
		Shader(vertexPath, fragmentPath) {
		storeAllUniformLocation();
	}

	virtual void storeAllUniformLocation() {
		m_OriginalTexture->storeLocation(m_ShaderID);
		m_BlurredTexture->storeLocation(m_ShaderID);
	}
	
};

#endif // !_BLOOM_COMBINE_SHADER_H_

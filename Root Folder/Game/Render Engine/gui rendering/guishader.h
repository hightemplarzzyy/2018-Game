#pragma once

#include "../shaders/shader.h"
#include "../shaders/uniform1f.h"
#include "../shaders/uniformbool.h"
#include "../shaders/uniformvec3.h"
#include "../shaders/uniformvec4.h"
#include "../shaders/uniformsampler.h"

class GuiShader :public Shader {
public:
	Uniform1f * alpha = new Uniform1f("alpha");
	UniformBool * flipTexture = new UniformBool("flipTexture");	//ÊÇ·ñ·­×ª×ø±ê
	UniformBool * usesBlur = new UniformBool("usesBlur");
	UniformBool * useOverrideColor = new UniformBool("useOverrideColor");
	UniformVec3 * overrideColor = new UniformVec3("overrideColor");
	UniformVec4 * transform = new UniformVec4("transform");
	UniformSampler * blurTexture = new UniformSampler("blurTexture");
	UniformSampler * guiTexture = new UniformSampler("guiTexture");

	GuiShader(const char * vertexPath, const char * fragmentPath) :
		Shader(vertexPath, fragmentPath) {
		storeAllUniformLocation();
		enable();
		guiTexture->load(0);
		blurTexture->load(1);
		disable();
	}

	virtual void storeAllUniformLocation() {
		alpha->storeLocation(m_ShaderID);
		flipTexture->storeLocation(m_ShaderID);
		usesBlur->storeLocation(m_ShaderID);
		useOverrideColor->storeLocation(m_ShaderID);
		overrideColor->storeLocation(m_ShaderID);
		transform->storeLocation(m_ShaderID);
		blurTexture->storeLocation(m_ShaderID);
		guiTexture->storeLocation(m_ShaderID);
	}
	   
};
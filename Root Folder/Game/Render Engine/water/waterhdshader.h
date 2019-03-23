#pragma once

#include "../shaders/shader.h"
#include "../shaders/uniformmat4.h"
#include "../shaders/uniform1f.h"
#include "../shaders/uniformvec3.h"
#include "../shaders/uniformvec2.h"
#include "../shaders/uniformsampler.h"

class WaterHdShader : public Shader 
{
public:
	UniformMat4 projectionMatrix = UniformMat4("projectionMatrix");
	UniformMat4 viewMatrix = UniformMat4("viewMatrix");
	UniformMat4 model = UniformMat4("model");
	Uniform1f worldRadius = Uniform1f("worldRadius");
	Uniform1f waveTime = Uniform1f("waveTime");
	Uniform1f waterHeight = Uniform1f("waterHeight");
	Uniform1f fadeOutPeriod = Uniform1f("fadeOutPeriod");
	UniformVec3 lightDirection = UniformVec3("lightDirection");
	UniformVec3 lightColour = UniformVec3("lightColour");
	UniformVec3 cameraPosition = UniformVec3("cameraPosition");
	UniformSampler depthTexture = UniformSampler("depthTexture");
	UniformSampler reflectionTexture = UniformSampler("reflectionTexture");
	UniformVec2 frustumNearFar = UniformVec2("frustumNearFar");
	UniformVec2 worldCenter = UniformVec2("worldCenter");
	Uniform1f amplitude = Uniform1f("amplitude");
	UniformVec3 skyColour = UniformVec3("skyColour");
	UniformVec2 mistValues = UniformVec2("mistValues");
	UniformVec3 mistColour = UniformVec3("mistColour");

public:
	WaterHdShader() = default;

	WaterHdShader(const char* vertexPath, const char* fragmentPath) : Shader(vertexPath, fragmentPath)
	{
		storeAllUniformLocation();
	}

	virtual void storeAllUniformLocation() 
	{
		projectionMatrix.storeLocation(m_ShaderID);
		viewMatrix.storeLocation(m_ShaderID);
		worldRadius.storeLocation(m_ShaderID);
		waveTime.storeLocation(m_ShaderID);
		waterHeight.storeLocation(m_ShaderID);
		fadeOutPeriod.storeLocation(m_ShaderID);
		lightDirection.storeLocation(m_ShaderID);
		lightColour.storeLocation(m_ShaderID);
		cameraPosition.storeLocation(m_ShaderID);
		reflectionTexture.storeLocation(m_ShaderID);
		depthTexture.storeLocation(m_ShaderID);
		frustumNearFar.storeLocation(m_ShaderID);
		worldCenter.storeLocation(m_ShaderID);
		amplitude.storeLocation(m_ShaderID);
		skyColour.storeLocation(m_ShaderID);
		mistValues.storeLocation(m_ShaderID);
		mistColour.storeLocation(m_ShaderID);
		model.storeLocation(m_ShaderID);
		return;
	}
};

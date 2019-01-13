#pragma once

#include "depthoffieldshader.h"
#include "../post processing/postprocessingfilter.h"
#include "../../Source/main/CamerManager.h"

class CombineFilter :public PostProcessingFilter {
public:
	CombineFilter() :PostProcessingFilter(
		new DepthOfFieldShader(
			"Render Engine/post processing/basicpostprocessing.vert",
			"Render Engine/depth of field/combine.frag")) {

	}

	virtual void prepareShader(Shader * shader) {
		float focusDistance = CameraManager::pcamera->getAimDistance() / 2;
		((DepthOfFieldShader *)shader)->m_AimDistance->load(focusDistance);
	}

};


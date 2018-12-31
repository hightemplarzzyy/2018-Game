#pragma once

#include "../postProcessing/PostProcessingFilter.h"
#include "../environment/environment.h"
#include "RadialBlurShader.h"

class RadialBlur : public PostProcessingFilter {
public:
	RadialBlur(int width, int height) :
		PostProcessingFilter(new RadialBlurShader(
			"Render Engine/postProcessing/basicPostProcessing.vert",
			"Render Engine/bloom/combine.frag"), width, height, false) {
	}

	virtual void prepareShader(Shader * shader) {
		vec2 * pSunCoords = EnvironmentVariables::getSunScreenPosition();
		if (pSunCoords != NULL) {
			((RadialBlurShader *)shader)->lightPositionOnScreen->load(*pSunCoords);
		}
	}

};
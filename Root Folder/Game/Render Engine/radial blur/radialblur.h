#pragma once

#include "../post processing/PostProcessingFilter.h"
#include "../environment/environment.h"
#include "RadialBlurShader.h"

class RadialBlur : public PostProcessingFilter {
public:
	RadialBlur(int width, int height) :
		PostProcessingFilter(new RadialBlurShader(
			"Render Engine/post processing/basicPostProcessing.vert",
			"Render Engine/radial blur/radialblur.frag"), width, height, false) {
	}

	virtual void prepareShader(Shader * shader) {
		vec2 * pSunCoords = EnvironmentVariables::getSunScreenPosition();
		if (pSunCoords != NULL) {
			((RadialBlurShader *)shader)->lightPositionOnScreen->load(*pSunCoords);
		}
	}

};
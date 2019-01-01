#pragma once

#include "../postProcessing/GaussianBlur/GaussianBlur.h"
#include "CombineFilter.h"

class DepthOfFieldEffect :public PostProcessingPipeline {
private:
	PostProcessingPipeline * m_guassianBlur;
	PostProcessingFilter * m_combineFilter;

public:
	DepthOfFieldEffect(int blurWidth, int blurHeight) {
		m_guassianBlur = new GaussianBlur(blurWidth, blurHeight);
		m_combineFilter = new CombineFilter();
	}

	virtual void carryOutProcessing(GLuint colourTextture, GLuint depthTexture, bool renderToScreen) {
		((GaussianBlur *)m_guassianBlur)->carryOutProcessing(colourTextture, depthTexture, false);
		((CombineFilter *)m_combineFilter)->applyFilter(renderToScreen, { colourTextture,((GaussianBlur *)m_guassianBlur)->getOutputTexture(),depthTexture });
	}

	virtual void cleanUp() {
		((GaussianBlur *)m_guassianBlur)->cleanUp();
		((CombineFilter *)m_combineFilter)->cleanUp();
	}

	virtual GLuint getOutputTexture() {
		return ((CombineFilter *)m_combineFilter)->getOutputTexture();
	}

	GLuint getBlurredTexture() {
		return ((GaussianBlur *)m_guassianBlur)->getOutputTexture();
	}

};
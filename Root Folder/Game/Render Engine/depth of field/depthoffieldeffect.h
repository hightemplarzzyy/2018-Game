#pragma once

#include "../post processing/gaussian blur/gaussianblur.h"
#include "combinefilter.h"

class DepthOfFieldEffect :public PostProcessingPipeline {
private:
	PostProcessingPipeline * m_GuassianBlur;
	PostProcessingFilter * m_CombineFilter;

public:
	DepthOfFieldEffect(int blurWidth, int blurHeight) {
		m_GuassianBlur = new GaussianBlur(blurWidth, blurHeight);
		m_CombineFilter = new CombineFilter();
	}

	virtual void carryOutProcessing(GLuint colourTextture, GLuint depthTexture, bool renderToScreen) {
		((GaussianBlur *)m_GuassianBlur)->carryOutProcessing(colourTextture, depthTexture, false);
		((CombineFilter *)m_CombineFilter)->applyFilter(renderToScreen, { colourTextture,((GaussianBlur *)m_GuassianBlur)->getOutputTexture(),depthTexture });
	}

	virtual void cleanUp() {
		((GaussianBlur *)m_GuassianBlur)->cleanUp();
		((CombineFilter *)m_CombineFilter)->cleanUp();
	}

	virtual GLuint getOutputTexture() {
		return ((CombineFilter *)m_CombineFilter)->getOutputTexture();
	}

	GLuint getBlurredTexture() {
		return ((GaussianBlur *)m_GuassianBlur)->getOutputTexture();
	}

};
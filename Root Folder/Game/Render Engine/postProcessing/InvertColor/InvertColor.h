#pragma once

#include "../PostProcessingPipeline.h"
#include "../PostProcessingFilter.h"
#include "InvertColorShader.h"

//不要当作参数传入，请使用引用
class InvertColor:public PostProcessingPipeline {
private:
	InvertColorShader * ishader;
	PostProcessingFilter * iFilter;

public:
	InvertColor(int width, int heigh, Window * window) {
		ishader = new InvertColorShader("Render Engine/postProcessing/InvertColor/InvertColor.vert",
			"Render Engine/postProcessing/InvertColor/InvertColor.frag");
		iFilter = new PostProcessingFilter(ishader, width, heigh,false,window);
	}

	virtual GLuint getOutputTexture() {
		return iFilter->getOutputTexture();
	}

	virtual void carryOutProcessing(GLuint colourTextture, GLuint depthTexture, bool renderToScreen, Window * window) {

		
		iFilter->applyFilter(false, { colourTextture }, window);

		if (renderToScreen) {
			iFilter->blitToScreen();
		}
	}

	virtual void cleanUp() {
		iFilter->cleanUp();
	}

	~InvertColor() {
		delete ishader;
		delete iFilter;
	}
};

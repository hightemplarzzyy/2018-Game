#pragma once

#include "../PostProcessingPipeline.h"
#include "../PostProcessingFilter.h"
#include "InvertColorShader.h"

//��Ҫ�����������룬��ʹ������
class InvertColor:public PostProcessingPipeline {
private:
	InvertColorShader * ishader;
	PostProcessingFilter * iFilter;

public:
	InvertColor(int width, int heigh) {
		ishader = new InvertColorShader("Render Engine/post processing/invert color/InvertColor.vert",
			"Render Engine/post processing/invert color/InvertColor.frag");
		iFilter = new PostProcessingFilter(ishader, width, heigh,false);
	}

	virtual GLuint getOutputTexture() {
		return iFilter->getOutputTexture();
	}

	virtual void carryOutProcessing(GLuint colourTextture, GLuint depthTexture, bool renderToScreen) {

		
		iFilter->applyFilter(false, { colourTextture });

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

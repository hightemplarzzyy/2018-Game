#ifndef _GAUSSIAN_BLUR_H_
#define _GAUSSIAN_BLUR_H_

#include "../PostProcessingPipeline.h"
#include "../PostProcessingFilter.h"
#include "VerticalBlurShader.h"
#include "HorizontalBlurShader.h"

//��Ҫ�����������룬��ʹ������
class GaussianBlur :public PostProcessingPipeline {
private:
	
	VerticalBlurShader * vshader;
	HorizontalBlurShader * hshader;

	PostProcessingFilter * verticalBlur;
	PostProcessingFilter * horizontalBlur;

public:
	GaussianBlur(int width, int heigh) {
		vshader = new VerticalBlurShader("Render Engine/post processing/gaussian blur/verticalblur.vert", "Render Engine/post processing/Gaussian Blur/blur.frag");
		vshader->enable();
		vshader->height->load(float(heigh));
		vshader->disable();
		hshader = new HorizontalBlurShader("Render Engine/post processing/gaussian blur/horizontalblur.vert", "Render Engine/post processing/Gaussian Blur/blur.frag");
		hshader->enable();
		hshader->width->load(float(width));
		hshader->disable();
		verticalBlur = new PostProcessingFilter(vshader, width, heigh, false);
		horizontalBlur = new PostProcessingFilter(hshader, width, heigh, false);
	}

	~GaussianBlur() {
		delete vshader;
		delete hshader;
		delete verticalBlur;
		delete horizontalBlur;
	}

	virtual GLuint getOutputTexture() {
		return horizontalBlur->getOutputTexture();
	}

	virtual void carryOutProcessing(GLuint colourTextture, GLuint depthTexture, bool renderToScreen) {
		
		GLuint vertBlurred = verticalBlur->applyFilter(false, { colourTextture });
		horizontalBlur->applyFilter(false, { vertBlurred });

		if (renderToScreen) {
			horizontalBlur->blitToScreen();
		}
	}

	virtual void cleanUp() {
		verticalBlur->cleanUp();
		horizontalBlur->cleanUp();
	}

};
#endif // !_GAUSSIAN_BLUR_H_

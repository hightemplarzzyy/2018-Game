#ifndef _GAUSSIAN_BLUR_H_
#define _GAUSSIAN_BLUR_H_

#include "../PostProcessingPipeline.h"
#include "../PostProcessingFilter.h"
#include "VerticalBlurShader.h"
#include "HorizontalBlurShader.h"

//不要当作参数传入，请使用引用
class GaussianBlur :public PostProcessingPipeline {
private:
	
	VerticalBlurShader * vshader;
	HorizontalBlurShader * hshader;

	PostProcessingFilter * verticalBlur;
	PostProcessingFilter * horizontalBlur;

public:
	GaussianBlur(int width, int heigh,Window * window) {
		vshader = new VerticalBlurShader("Render Engine/postProcessing/GaussianBlur/verticalBlur.vert", "Render Engine/postProcessing/GaussianBlur/blur.frag");
		vshader->enable();
		vshader->height->load(float(heigh));
		vshader->disable();
		hshader = new HorizontalBlurShader("Render Engine/postProcessing/GaussianBlur/horizontalBlur.vert", "Render Engine/postProcessing/GaussianBlur/blur.frag");
		hshader->enable();
		hshader->width->load(float(width));
		hshader->disable();
		verticalBlur = new PostProcessingFilter(vshader, width, heigh, false, window);
		horizontalBlur = new PostProcessingFilter(hshader, width, heigh, false, window);
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

	virtual void carryOutProcessing(GLuint colourTextture, GLuint depthTexture, bool renderToScreen,Window * window) {
		
		GLuint vertBlurred = verticalBlur->applyFilter(false, { colourTextture }, window);
		horizontalBlur->applyFilter(false, { vertBlurred }, window);

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

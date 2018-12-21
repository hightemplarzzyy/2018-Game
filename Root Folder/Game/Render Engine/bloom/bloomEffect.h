#ifndef _BLOOM_EFFECT_H_
#define _BLOOM_EFFECT_H_

#include "../postProcessing/PostProcessingPipeline.h"
#include "../postProcessing/PostProcessingFilter.h"
#include "../postProcessing/GaussianBlur/GaussianBlur.h"
#include "BloomCombineShader.h"

//不要当作参数传入，请使用引用
class BloomEffect :public PostProcessingPipeline {
private:
	PostProcessingFilter * m_brightFilter;
	PostProcessingFilter * m_combineFilter;
	GaussianBlur * m_gaussian;
	BloomCombineShader * m_bloomshader;
	BloomCombineShader * m_brightpassshader;

public:

	BloomEffect(int blurWidth, int blurHeight) {
		m_bloomshader = new BloomCombineShader(
			"Render Engine/postProcessing/basicPostProcessing.vert",
			"Render Engine/bloom/combine.frag"
		);
		m_brightpassshader = new BloomCombineShader(
			"Render Engine/postProcessing/basicPostProcessing.vert",
			"Render Engine/bloom/brightPass.frag"
		);

		m_brightFilter = new PostProcessingFilter(m_brightpassshader);
		m_gaussian = new GaussianBlur(blurWidth, blurHeight);
		m_combineFilter = new PostProcessingFilter(m_bloomshader);
	}

	~BloomEffect() {
		delete m_brightFilter;
		delete m_combineFilter;
		delete m_gaussian;
		delete m_bloomshader;
		delete m_brightpassshader;
	}

	virtual void carryOutProcessing(GLuint colourTextture, GLuint depthTexture, bool renderToScreen) {
		m_brightFilter->applyFilter(false, { colourTextture });
		m_gaussian->carryOutProcessing(m_brightFilter->getOutputTexture(), depthTexture, false);
		GLuint gaussianTexture = m_gaussian->getOutputTexture();
		m_combineFilter->applyFilter(renderToScreen, { colourTextture,gaussianTexture });
	}

	virtual GLuint getOutputTexture() {
		return m_combineFilter->getOutputTexture();
	}

	virtual void cleanUp() {
		m_brightFilter->cleanUp();
		m_combineFilter->cleanUp();
	}
	
};

#endif // !_BLOOM_EFFECT_H_

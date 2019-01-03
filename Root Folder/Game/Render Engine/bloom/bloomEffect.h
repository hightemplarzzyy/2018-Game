#ifndef _BLOOM_EFFECT_H_
#define _BLOOM_EFFECT_H_

#include "../post processing/postprocessingpipeline.h"
#include "../post processing/postprocessingfilter.h"
#include "../post processing/gaussian blur/gaussianblur.h"
#include "BloomCombineShader.h"

//不要当作参数传入，请使用引用
class BloomEffect :public PostProcessingPipeline {
private:
	PostProcessingFilter * m_BrightFilter;
	PostProcessingFilter * m_CombineFilter;
	GaussianBlur * m_GaussianBlur;
	BloomCombineShader * m_BloomShader;
	BloomCombineShader * m_BrightPassShader;

public:

	BloomEffect(int blurWidth, int blurHeight) {
		m_BloomShader = new BloomCombineShader(
			"Render Engine/post processing/basicpostprocessing.vert",
			"Render Engine/bloom/combine.frag"
		);
		m_BrightPassShader = new BloomCombineShader(
			"Render Engine/post processing/basicpostprocessing.vert",
			"Render Engine/bloom/brightPass.frag"
		);

		m_BrightFilter = new PostProcessingFilter(m_BrightPassShader);
		m_GaussianBlur = new GaussianBlur(blurWidth, blurHeight);
		m_CombineFilter = new PostProcessingFilter(m_BloomShader);
	}

	~BloomEffect() {
		delete m_BrightFilter;
		delete m_CombineFilter;
		delete m_GaussianBlur;
		delete m_BloomShader;
		delete m_BrightPassShader;
	}

	virtual void carryOutProcessing(GLuint colourTextture, GLuint depthTexture, bool renderToScreen) {
		m_BrightFilter->applyFilter(false, { colourTextture });
		m_GaussianBlur->carryOutProcessing(m_BrightFilter->getOutputTexture(), depthTexture, false);
		GLuint gaussianTexture = m_GaussianBlur->getOutputTexture();
		m_CombineFilter->applyFilter(renderToScreen, { colourTextture,gaussianTexture });
	}

	virtual GLuint getOutputTexture() {
		return m_CombineFilter->getOutputTexture();
	}

	virtual void cleanUp() {
		m_BrightFilter->cleanUp();
		m_CombineFilter->cleanUp();
	}
	
};

#endif // !_BLOOM_EFFECT_H_

#ifndef _POSTPROCESSING_PIPELINE_H_
#define _POSTPROCESSING_PIPELINE_H_

class PostProcessingPipeline {
	virtual void carryOutProcessing(GLuint colourTextture, GLuint depthTexture, bool renderToScreen) = 0;
	virtual GLuint getOutputTexture() = 0;
	virtual void cleanUp() = 0;
};

#endif // !_POSTPROCESSING_PIPELINE_H_

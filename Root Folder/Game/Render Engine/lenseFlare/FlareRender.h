#pragma once
#include <vector>

#include "../guiRendering/GuiShader.h"
#include "../buffers/vertexarray.h"
#include "../toolbox/Query.h"
#include "FlareTexture.h"

class FlareRender {
private:
	static float POSITIONS[];
	static float TEST_BOX_WIDTH;
	static float TEST_BOX_HEIGHT;
	static float TOTAL_SAMPLES;

	GuiShader * m_shader;
	VertexArray m_vao;

	Query * m_query;	//ÕÚµ²²éÑ¯
	float m_coverage = 1;

public:
	FlareRender();
	~FlareRender();

	void render(std::vector<FlareTexture> & flares, std::vector<vec3> & data, float brightness);
	void cleanUp();
	void doOcclusionTest(vec2 * pvec2);
	
private:
	void prepare(float brightness);
	void renderFlare(FlareTexture & flare, vec3 & data);
	void endRendering();
	void initShader();
	float getActualSize(float sizeFactor);


};
#pragma once
#include <vector>

#include "../gui rendering/guishader.h"
#include "../buffers/vertexarray.h"
#include "../toolbox/Query.h"
#include "FlareTexture.h"

class FlareRenderer {
private:
	static float POSITIONS[];
	static float TEST_BOX_WIDTH;
	static float TEST_BOX_HEIGHT;
	static float TOTAL_SAMPLES;

	GuiShader * m_Shader;
	VertexArray m_Vao;

	Query * m_Query;	//ÕÚµ²²éÑ¯
	float m_Coverage = 1;

public:
	FlareRenderer();
	~FlareRenderer();

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
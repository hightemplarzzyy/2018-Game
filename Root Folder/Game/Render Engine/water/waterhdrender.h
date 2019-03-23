#pragma once

#include "waterframebuffer.h"
#include "water.h"
#include "waterhdshader.h"
#include "../../Source/main/camera.h"
#include "../toolbox/maths/maths_func.h"
#include "../basics/DIsplayManager.h"

class WaterHdRenderer 
{
private:
	static int REFLECTION_TEX_UNIT;
	static int DEPTH_TEX_UNIT;

	static float WAVE_PERIOD;

	WaterFrameBuffers fbos;
	WaterHdShader shader;
	float waveTime = 0;
	Water water;

public:
	WaterHdRenderer(mat4 projectionMatrix, Water &w, WaterFrameBuffers &fbo, float N, float F);
	void render(Camera &camera);

private:
	void prepare(Camera &camera);
	void stopRendering();
	void updateWaveTime();
	void draw();
};


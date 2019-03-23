#pragma  once

#include <vector>
#include <memory>
#include <stb_image.h>
#include <string>
#include "../../Source/main/camera.h"
#include "../toolbox/maths/maths_func.h"
#include "../basics/DIsplayManager.h"
#include "water.h"
#include "watershader.h"

class WaterRenderer 
{
public:
	static float WAVE_PERIOD;

private:
	WaterShader shader;
	float waveTime;
	Water water;

public:
	WaterRenderer(mat4 projectionMatrix, Water &w);
	void render(Camera &camera);
	void unbind();

private:
	void prepare(Camera &camera);
	void updateWaveTime();
	void draw();
};
#pragma once

/**
	WaterMasterRender有两种模式（OPTION控制）：
	1.无反射现象的水面
	2.有反射现象的水面，这时需要向render调用函数的赋参数值：
		refractionEvent  为渲染水面以上物体的函数
		reflectEvent  为渲染水面以下物体的函数
*/


#include <functional>
#include "waterframebuffer.h"
#include "waterrender.h"
#include "water.h"
#include "waterhdrender.h"
#include "waterhdshader.h"
#include "watershader.h"
#include "../../Source/main/camera.h"
#include "../toolbox/maths/maths_func.h"
#include "../toolbox/maths/vec4.h"

#define OPTION true

class WaterMasterRenderer 
{
private:
	static float REFRACTION_BIAS;

	WaterFrameBuffers waterFbos;
	Water water;

	WaterRenderer waterRenderer;
	WaterHdRenderer waterHdRenderer;
	Camera* camera;
	
public:
	WaterMasterRenderer(Camera *camera, Water &w, mat4 projection);
	void render(const std::function<void()> &refractionEvent = {}, const std::function<void()> &reflectEvent = {});
	void updateWaterTextures(const std::function<void()> &refractionEvent, const std::function<void()> &reflectEvent);
	void cleanUp();
};
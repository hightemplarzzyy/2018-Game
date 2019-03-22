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
	Window *window;
	Camera* camera;
	
public:
	WaterMasterRenderer() = default;

	WaterMasterRenderer(Camera *camera, Water &w, Window* win)
	{
		this->camera = camera;
		this->water = w;
		this->window = win;
		waterFbos.init();
		mat4 projection = mat4::perspective(camera->getFOV(), window->getWidth() / window->getHeight(), camera->getNearPlane(), camera->getFarPlane());
		waterHdRenderer = WaterHdRenderer(projection, water, waterFbos, 0.1f, 1000.0f);
		waterRenderer = WaterRenderer(projection, water);
	}

	void render(const std::function<void()> &refractionEvent = {}, const std::function<void()> &reflectEvent = {})
	{
		if (OPTION && refractionEvent != nullptr && reflectEvent != nullptr)
		{
			updateWaterTextures(refractionEvent, reflectEvent);
			waterHdRenderer.render(*camera);
		}
		else
			waterRenderer.render(*camera);
	}

	void updateWaterTextures(const std::function<void()> &refractionEvent, const std::function<void()> &reflectEvent)
	{
		if (OPTION)
		{
			glEnable(GL_CLIP_DISTANCE0);
			waterFbos.bindRefractionFrameBuffer();
			glClear(GL_DEPTH_BUFFER_BIT);
			glDisable(GL_BLEND);
			glCullFace(GL_BACK);
			glEnable(GL_DEPTH_TEST);
			refractionEvent();
			waterFbos.unbindCurrentFrameBuffer(window->getWidth(), window->getHeight());
			
			camera->reflect(water.height);
			waterFbos.bindReflectionFrameBuffer();
			glClearColor(0.0, 0.3, 0.5, 1.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glDisable(GL_BLEND);
			glCullFace(GL_BACK);
			glEnable(GL_DEPTH_TEST);
			reflectEvent();
			waterFbos.unbindCurrentFrameBuffer(window->getWidth(), window->getHeight());
			camera->reflect(water.height);

			glDisable(GL_CLIP_DISTANCE0);
		}
	}

	void cleanUp() 
	{
		waterFbos.cleanUp();
	}
};

float WaterMasterRenderer::REFRACTION_BIAS = 0.3f;

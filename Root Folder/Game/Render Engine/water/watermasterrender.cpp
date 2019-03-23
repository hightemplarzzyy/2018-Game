#include "watermasterrender.h"

float WaterMasterRenderer::REFRACTION_BIAS = 0.3f;

WaterMasterRenderer::WaterMasterRenderer(Camera *camera, Water &w, mat4 projection) :
	waterHdRenderer(projection, water, waterFbos, 0.1f, 1000.0f),
	waterRenderer(projection, water)
{
	this->camera = camera;
	this->water = w;
	waterFbos.init();
}

void WaterMasterRenderer::render(const std::function<void()> &refractionEvent, const std::function<void()> &reflectEvent)
{
	if (OPTION && refractionEvent != nullptr && reflectEvent != nullptr)
	{
		updateWaterTextures(refractionEvent, reflectEvent);
		waterHdRenderer.render(*camera);
	}
	else
		waterRenderer.render(*camera);
}

void WaterMasterRenderer::updateWaterTextures(const std::function<void()> &refractionEvent, const std::function<void()> &reflectEvent)
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
		waterFbos.unbindCurrentFrameBuffer();

		camera->reflect(vec3(0.0, 1.0, 0.0));
		waterFbos.bindReflectionFrameBuffer();
		glClearColor(0.0, 0.3, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_BLEND);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);
		reflectEvent();
		waterFbos.unbindCurrentFrameBuffer();
		camera->reflect(vec3(0.0, -1.0, 0.0));

		glDisable(GL_CLIP_DISTANCE0);
	}
}

void WaterMasterRenderer::cleanUp()
{
	waterFbos.cleanUp();
}
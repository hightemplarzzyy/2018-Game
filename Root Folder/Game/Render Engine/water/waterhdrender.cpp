#include "waterhdrender.h"

float WaterHdRenderer::WAVE_PERIOD = 3.9f;

WaterHdRenderer::WaterHdRenderer(mat4 projectionMatrix, Water &w, WaterFrameBuffers &fbo, float N, float F)
	:shader("Render Engine/water/waterhd.vert", "Render Engine/water/waterhd.frag")
{
	this->fbos = fbo;
	water = w;
	vec3 lightDirection = vec3(0.4f, -1.0f, 0.2f);
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	mat4 model = mat4::translation(vec3(water.x, water.height, water.z));

	shader.enable();
	shader.projectionMatrix.load(projectionMatrix);
	shader.model.load(model);
	shader.amplitude.load(Water::AMPLITUDE);
	shader.worldRadius.load(10.0);
	shader.fadeOutPeriod.load(10.0);
	shader.worldCenter.load(vec2(0.0f, 0.0f));
	shader.frustumNearFar.load(vec2(N, F));
	shader.mistValues.load(vec2(20, 120));
	shader.mistColour.load(vec3(1.0, 222.0 / 255.0, 210.0 / 255.0));
	shader.skyColour.load(vec3(1, 0.87f, 0.6f));
	shader.waterHeight.load(water.height);
	shader.lightDirection.load(lightDirection);
	shader.lightColour.load(lightColor);
	shader.reflectionTexture.load(0);
	shader.depthTexture.load(1);
}

void WaterHdRenderer::render(Camera &camera)
{
	prepare(camera);
	draw();
	stopRendering();
}

void WaterHdRenderer::prepare(Camera &camera)
{
	glCullFace(GL_BACK);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(false);

	shader.enable();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fbos.reflectionTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, fbos.refractionDepthTexture);

	shader.viewMatrix.load(camera.CreateViewMatrix());
	shader.cameraPosition.load(camera.getPosition());

	updateWaveTime();
}

void WaterHdRenderer::stopRendering()
{
	glDisable(GL_BLEND);
	glBindVertexArray(0);
	glDepthMask(true);
}

void WaterHdRenderer::updateWaveTime()
{
	waveTime += DisplayManager::getDelta();
	if (waveTime > WaterHdRenderer::WAVE_PERIOD) waveTime -= WaterHdRenderer::WAVE_PERIOD;
	shader.enable();
	shader.waveTime.load(waveTime / WaterHdRenderer::WAVE_PERIOD);
}

void WaterHdRenderer::draw()
{
	if (water.vao == 0)
	{
		std::vector<float> vertexData = WaterGenerator::generate(water.pointCount - 1, 0);
		water.vertexCount = vertexData.size() / WaterGenerator::VERTEX_SIZE_BYTES;

		glGenVertexArrays(1, &water.vao);
		glBindVertexArray(water.vao);

		unsigned int vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), &vertexData[0], GL_STATIC_DRAW);
		float stride = 6 * sizeof(float);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));

	}
	glBindVertexArray(water.vao);
	glDrawArrays(GL_TRIANGLES, 0, water.vertexCount);
}
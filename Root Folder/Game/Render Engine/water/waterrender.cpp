#include "waterrender.h"

float WaterRenderer::WAVE_PERIOD = 3.5f;

WaterRenderer::WaterRenderer(mat4 projectionMatrix, Water &w)
	: shader("Render Engine/water/water.vert", "Render Engine/water/water.frag")
{
	waveTime = 0;
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
	shader.mistValues.load(vec2(20, 120));
	shader.mistColour.load(vec3(1.0, 222.0 / 255.0, 210.0 / 255.0));
	shader.waterHeight.load(water.height);
	shader.lightDirection.load(lightDirection);
	shader.lightColour.load(lightColor);
}

void WaterRenderer::render(Camera &camera)
{
	prepare(camera);
	draw();
	unbind();
}

void WaterRenderer::unbind()
{
	glBindVertexArray(0);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_MULTISAMPLE);
	glDepthMask(true);
}

void WaterRenderer::prepare(Camera &camera)
{
	glCullFace(GL_BACK);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(false);

	shader.enable();
	shader.viewMatrix.load(camera.CreateViewMatrix());
	shader.cameraPosition.load(camera.getPosition());
	updateWaveTime();
}

void WaterRenderer::updateWaveTime()
{
	waveTime += DisplayManager::getDelta();
	if (waveTime > WaterRenderer::WAVE_PERIOD) waveTime -= WaterRenderer::WAVE_PERIOD;
	shader.enable();
	shader.waveTime.load(waveTime / WaterRenderer::WAVE_PERIOD);
}

void WaterRenderer::draw()
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
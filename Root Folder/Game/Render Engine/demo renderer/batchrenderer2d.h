#pragma once

#include "renderer2d.h"
#include "../buffers/indexbuffer.h"

#define MAX_SPRITES		60000
#define VERTEX_SIZE		sizeof(VertexData)
#define SPRITE_SIZE		VERTEX_SIZE * 4
#define BUFFER_SIZE		SPRITE_SIZE * MAX_SPRITES
#define INDICIES_SIZE	MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX 1

class BatchRenderer2D : public Renderer2D{
private:
	GLuint m_VAO;
	GLuint m_VBO;
	IndexBuffer *m_IBO;
	GLsizei m_Indexcount;
	VertexData *m_Buffer;
public:
	BatchRenderer2D();
	~BatchRenderer2D();
	void begin();
	void submit(const Renderable2D* renderable) override;
	void end();
	void flush() override;

private:
	void init();
};
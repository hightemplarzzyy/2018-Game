#pragma once

#include "renderable2d.h"

class StaticSprite : public Renderable2D {
private:
	IndexBuffer* m_IndexBuffer;
	VertexArray* m_VertexArray;
	SimpleShader& m_SimpleShader;
	
public:
	StaticSprite(float x, float y, float width, float height, const vec4 &color, SimpleShader &shader);
	~StaticSprite();

	inline const VertexArray* getVAO() const { return m_VertexArray; }
	inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }

	inline SimpleShader& getShader() const { return m_SimpleShader; }
};

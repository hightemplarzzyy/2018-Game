#pragma once

#include "../../Render Engine/buffers/buffer.h"
#include "../../Render Engine/buffers/indexbuffer.h"
#include "../../Render Engine/buffers/vertexarray.h"
#include "../../Render Engine/toolbox/maths/maths_func.h"
#include "../../Render Engine/demo renderer/smipleshader.h"

struct VertexData {
	vec3 vertex;
	vec4 color;

};

class Renderable2D {

protected:
	vec3 m_Position;
	vec2 m_Size;
	vec4 m_Color;

public:
	Renderable2D(vec3 position, vec2 size, vec4 color)
		:m_Position(position),m_Size(size),m_Color(color)
	{}

	virtual ~Renderable2D() {}

	inline const vec3& getPosition() const { return m_Position; }
	inline const vec2& getSize() const { return m_Size; }
	inline const vec4& getColor() const { return m_Color; }
};
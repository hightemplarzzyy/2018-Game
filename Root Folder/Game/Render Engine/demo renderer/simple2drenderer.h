#pragma once

#include <deque>
#include "../../Render Engine/demo renderer/renderer2d.h"
#include "../../Source/entity/staticsprite.h"

class Simple2DRenderer : public Renderer2D{
private:
	std::deque<const StaticSprite*> m_RenderQueue;

public:
	virtual void submit(const Renderable2D* renderable) override;
	virtual void flush() override;
};
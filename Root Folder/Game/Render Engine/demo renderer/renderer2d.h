#pragma once

#include <GL/glew.h>
#include "../toolbox/maths/maths_func.h"
#include "../../Source/entity/renderable2d.h"

class Renderer2D {

public:
	virtual void submit(const Renderable2D* renderable) = 0;
	virtual void flush() = 0;
};
#pragma once

#include "renderer2d.h"
#include "simple2drenderer.h"
#include "smipleshader.h"
#include "batchrenderer2d.h"
#include "../entity/renderable2d.h"
#include "../entity/staticsprite.h"
#include "../entity/sprite.h"

#include <time.h>

#define BATCH 1

class DemoBatchRenderer {
private:
	std::vector<Renderable2D*> m_Sprites;
	SimpleShader *m_Shader;

#if BATCH
	BatchRenderer2D m_Renderer;
#else
	Simple2DRenderer m_Renderer;
#endif

public:
	DemoBatchRenderer();
	~DemoBatchRenderer();

	void render();
	SimpleShader *getShader() { return m_Shader; }


};
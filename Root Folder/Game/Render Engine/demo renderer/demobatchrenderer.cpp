#include "demobatchrenderer.h"

DemoBatchRenderer::DemoBatchRenderer() {

	m_Shader = new SimpleShader("Source/shaders/basic.vert", "Source/shaders/basic.frag");
	m_Shader->enable();
	m_Shader->projection_matrix->load(mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));

	srand(time(NULL));

	for (float y = 0; y < 9.0f; y += 0.05) {
		for (float x = 0; x < 16.0f; x += 0.05) {
			m_Sprites.push_back(new

#if BATCH
				Sprite
#else
				StaticSprite
#endif
				(x, y, 0.04f, 0.04f, vec4(rand() % 1000 / 1000.0f, 0, 1, 1)
#if !BATCH
					, m_Shader
#endif
					));
		}
	}
}

DemoBatchRenderer::~DemoBatchRenderer() {

}

void DemoBatchRenderer::render() {

#if BATCH
	m_Renderer.begin();
#endif
	for (Renderable2D *s : m_Sprites)
		m_Renderer.submit(s);
#if BATCH
	m_Renderer.end();
#endif
	m_Renderer.flush();
	std::cout << m_Sprites.size() << std::endl;

}
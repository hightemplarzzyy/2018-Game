#include "simple2drenderer.h"

void Simple2DRenderer::submit(const Renderable2D* renderable) {

	m_RenderQueue.push_back((StaticSprite*) renderable);

}
void Simple2DRenderer::flush() {

	while (!m_RenderQueue.empty()) {
		const StaticSprite* sprite = m_RenderQueue.front();
		sprite->getVAO()->bind();
		sprite->getIBO()->bind();

		sprite->getShader().model_matrix->load(mat4::translation(sprite->getPosition()));
		glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

		sprite->getIBO()->unbind();
		sprite->getVAO()->unbind();

		m_RenderQueue.pop_front();
	}



}
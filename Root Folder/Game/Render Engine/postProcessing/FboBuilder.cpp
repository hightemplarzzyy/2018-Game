#include "FboBuilder.h"

FboBuilder::FboBuilder(int width, int height):
	m_width(width),m_height(height){
}


FboBuilder & FboBuilder::setDepthBuffer(DepthBufferType type) {
	m_depthBuffer = type;
	return *this;
}

FboBuilder & FboBuilder::repeatTexture() {
	m_clampEdege = false;
	return *this;
}

FboBuilder & FboBuilder::antialias(int samples) {
	m_antialiased = true;
	m_samples = samples;
	return *this;
}

FboBuilder & FboBuilder::nearestFilter() {
	m_linearFilter = false;
	return *this;
}

FboBuilder & FboBuilder::withAphaChannel(bool alpha) {
	m_alphaChannel = alpha;
	return *this;
}

FboBuilder & FboBuilder::noColourBuffer() {
	m_colourBufer = false;
	return *this;
}

Fbo * FboBuilder::creat() {
	return new Fbo(m_width, m_height, m_depthBuffer, m_colourBufer, m_linearFilter, m_clampEdege,
		m_alphaChannel, m_antialiased, m_samples);
}




#include "particleMaster.h"
#include "particleRender.h"


void ParticleMaster::init(mat4 & projectionMatrix) {
	renderer = ParticleRender(projectionMatrix);
}

void ParticleMaster::updateList(std::vector<Particle> & list, Camera & camera) {
	
	std::vector<Particle> ::iterator it;
	for (it = list.begin(); it != list.end(); it++) {
		bool isStillAlice = it->update(camera);
		if (!isStillAlice) {
			list.erase(it);
		}
	}
}

void ParticleMaster::update(Camera &camera) {

	std::map <ParticleTexture, std::vector<Particle>>::iterator it;

	for (it = particles.begin(); it != particles.end(); it++) {
		updateList(it->second, camera);
		if (it->second.empty()) {
			it = particles.erase(it);
		}
	}
	updateList(colourParticles, camera);
	updateList(colourAdditiveParticles,camera);
}

void ParticleMaster::reset() {
	particles.clear();
	colourParticles.clear();
	colourAdditiveParticles.clear();
}

void ParticleMaster::renderParticles(Camera & Camera) {
	renderer.render(particles, colourParticles, colourAdditiveParticles,Camera);
}

void ParticleMaster::addParticle(Particle & particle){
	particles[particle.getTexture()].push_back(particle);
}

void ParticleMaster::addColourPartivle(Particle & colourParticle, bool additive) {
	if (additive) {
		colourAdditiveParticles.push_back(colourParticle);
	}
	else {
		colourParticles.push_back(colourParticle);
	}
}


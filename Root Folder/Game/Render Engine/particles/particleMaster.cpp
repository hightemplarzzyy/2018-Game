#include "particleMaster.h"
#include "particleRender.h"

std::map <ParticleTexture, std::vector<Particle>> ParticleMaster::particles;
std::vector<Particle> ParticleMaster::colourParticles;
std::vector<Particle> ParticleMaster::colourAdditiveParticles;
ParticleRender ParticleMaster::renderer;


void ParticleMaster::init(mat4 projectionMatrix) {
	renderer = ParticleRender(projectionMatrix);
}

void ParticleMaster::updateList(std::vector<Particle> & list, Camera & camera) {
	
	std::vector<Particle> ::iterator it;
	for (it = list.begin(); it != list.end(); ) {
		bool isStillAlive = it->update(camera);
		if (!isStillAlive) {
			//it会指向下一个元数，那么这一轮不用递增
			it = list.erase(it);
		}
		else{
			it++;
		}
	}
}

void ParticleMaster::update(Camera &camera) {

	std::map <ParticleTexture, std::vector<Particle>>::iterator it;

	for (it = particles.begin(); it != particles.end();) {
		updateList(it->second, camera);
		if (it->second.empty()) {
			//it会指向下一个元数，那么这一轮不用递增
			it = particles.erase(it);
		}
		else {
			it++;
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


#ifndef _PARTICLES_MASTER_H_
#define _PARTICLES_MASTER_H_

#include <map>
#include <vector>

#include "particle.h"
#include "particleRender.h"
#include "particleTexture.h"


class ParticleMaster {

private:
	std::map <ParticleTexture, std::vector<Particle>> particles;
	std::vector<Particle> colourParticles;
	std::vector<Particle> colourAdditiveParticles;
	ParticleRender renderer;

public:
	void init(mat4 & projectionMatrix);
	void update(Camera & camera);
	void reset();
	void renderParticles(Camera & Camera);
	void addParticle(Particle &particle);
	void addColourPartivle(Particle & colourParticle, bool additive);
	void updateList(std::vector<Particle> & list, Camera & camera);
};

#endif // !_PARTICLES_MASTER_H_

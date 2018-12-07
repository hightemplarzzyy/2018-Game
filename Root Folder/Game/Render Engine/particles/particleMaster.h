#ifndef _PARTICLES_MASTER_H_
#define _PARTICLES_MASTER_H_

#include <map>
#include <vector>

#include "particle.h"
#include "particleRender.h"

class ParticleMaster {
private:
	static std::map <ParticleTexture, std::vector<Particle>> particles;
	static std::vector<Particle> colourParticles;
	static std::vector<Particle> colourAdditiveParticles;
	static ParticleRender renderer;
public:
	static void init(mat4 projectionMatrix);
	static void update(Camera camera);
	static void reset();
	static void renderParticles(Camera Camera);
	static void cleanUp();
	static void addParticle(Particle particle);
	static void addColourPartivle(Particle colourParticle, bool additive);
	static void updateList(std::vector<Particle> list, Camera camera);
};

#endif // !_PARTICLES_MASTER_H_

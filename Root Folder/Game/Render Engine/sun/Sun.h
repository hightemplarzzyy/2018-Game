#pragma once

#include "../particles/particle.h"
#include "../particles/particleTexture.h"

class Sun :public Particle {

private:
	static float DISTANCE;
	vec3 m_offset;

public:
	Sun(ParticleTexture texture, float scale, vec3 direction);
	
	void update(vec3 direction);

	vec3 getPosition();

};

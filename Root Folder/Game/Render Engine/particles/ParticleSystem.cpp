#include "ParticleSystem.h"
#include "../basics/DIsplayManager.h"
#include "particleMaster.h"


ParticleSystem::ParticleSystem(ParticleTexture texture, ParticleSpawn * spawn,
	float pps, float speed, float gravityComplient, float lifeLength, float scale) {
	m_spawn = spawn;
	m_pps = pps;
	m_averageSpeed = speed;
	m_gravityComplient = gravityComplient;
	m_averageLifeLength = lifeLength;
	m_averageScale = scale;
	m_texture = texture;
}

ParticleSystem::ParticleSystem(Color color, bool additive, ParticleSpawn * spawn,
	float pps, float speed, float gravityComplient, float lifeLength, float scale) {
	m_color = new Color(color.getColor());
	m_additive = additive;
	m_spawn = spawn;
	m_pps = pps;
	m_averageSpeed = speed;
	m_gravityComplient = gravityComplient;
	m_averageLifeLength = lifeLength;
	m_averageScale = scale;
}

ParticleSystem::~ParticleSystem() {
	delete m_color;
}

void ParticleSystem::setDirection(vec3 direction, float deviation) {
	m_direction = vec4(direction.x, direction.y, direction.z, 0.0f);
	m_directionDeviation = deviation * M_PI;
	m_isDirection = true;
}

void ParticleSystem::setDirectionLocalSpace() {
	m_directonLocalSpace = true;
}

void ParticleSystem::setFadeValue(float alpha, float fadeIn, float fadeOut) {
	m_alpha = alpha;
	m_fadeIn = fadeIn;
	m_fadeOut = fadeOut;
}

void ParticleSystem::setOffset(vec3 offset) {
	m_offset = vec4(offset.x, offset.y, offset.z, 0.0f);
}

void ParticleSystem::setXRotation(float speed) {
	m_hasXRotation = true;
	m_xRotSpeed = speed;
}

void ParticleSystem::setRandomizRotaion() {
	m_randomRotation = true;
}

void ParticleSystem::setSpeedError(float error) {
	m_speedError = error * m_averageSpeed;
}

void ParticleSystem::setLifeError(float error) {
	m_lifeError = error * m_averageLifeLength;
}

void ParticleSystem::setScaleError(float error) {
	m_scaleError = error * m_averageScale;
}

float ParticleSystem::generateValue(float average, float errorMargin) {
	float offset = float(rand() % 100) / 100.0f * errorMargin;
	return average + offset;
}

float ParticleSystem::generateRotation() {
	if (m_randomRotation) {
		return rand() % 360;
	}
	return 0;
}

void ParticleSystem::pulseParticles(vec3 center, float scale) {
	pulseParticles(mat4::translation(center), scale);
}

void ParticleSystem::pulseParticles(mat4 transform, float scale) {
	pulseParticles(transform, NULL, scale);
}

void ParticleSystem::generateParticles(vec3 center, float scale) {
	generateParticles(mat4::translation(center), scale);
}

void ParticleSystem::generateParticles(mat4 transform, float scale) {
	generateParticles(transform, NULL, scale);
}

void ParticleSystem::pulseParticles(vec3 center, Color * pColor, float scale) {
	pulseParticles(mat4::translation(center), pColor, scale);
}

void ParticleSystem::pulseParticles(mat4 transform, Color * pColor, float scale) {
	for (int i = 0; i < m_pps; i++) {
		emitParticle(transform, pColor, scale);
	}
}

void ParticleSystem::generateParticles(vec3 center, Color * pColor, float scale) {
	generateParticles(mat4::translation(center), pColor, scale);
}

void ParticleSystem::generateParticles(mat4 transform, Color * pColor, float scale) {
	float delta = DisplayManager::getDelta();
	float particlesToCreate = m_pps * delta;
	int count = floor(particlesToCreate);
	float particleProbility = fmod(particlesToCreate, 1);

	for (int i = 0; i < count; i++) {
		emitParticle(transform, pColor, scale);
	}

	if (float(rand() % 100) / 100.0f < particleProbility) {
		emitParticle(transform, pColor, scale);
	}
}

void ParticleSystem::emitParticle(mat4 transform, Color * pOverrideColour, float scaleFactor) {
	vec3 velocity;
	if (m_isDirection) {
		vec4 actualDir = m_directonLocalSpace ? m_direction * transform : m_direction;
		velocity = Maths::generateRandomUnitVectorWithinCone(vec3(actualDir.x, actualDir.y, actualDir.z), m_directionDeviation);
	}
	else {
		velocity = Maths::generteRandomUnitVector();
	}
	velocity.scale(generateValue(m_averageSpeed, m_speedError) * scaleFactor);
	float scale = generateValue(m_averageScale, m_scaleError) * scaleFactor;
	float lifeLength = generateValue(m_averageLifeLength, m_lifeError) * scaleFactor;

	vec4 spawnPosition = m_offset + m_spawn->getBaseSpawnPosition();
	spawnPosition = spawnPosition * transform;
	vec3 spawnPositionV3 = vec3(spawnPosition.x, spawnPosition.y, spawnPosition.z);
	
	Particle * p;
	//TODO:暂定这样添加例子的判定
	bool isTex = false;
	if (m_color == NULL) {
		p = new Particle(m_texture, spawnPositionV3, velocity, m_gravityComplient,
			lifeLength, generateRotation(), scale);
		isTex = true;
	}
	else {
		p = new Particle(pOverrideColour == NULL ? *m_color : *pOverrideColour, m_additive, spawnPositionV3, velocity,
			m_gravityComplient, lifeLength, generateRotation(), scale);
	}

	p->setFade(m_alpha, m_fadeIn, m_fadeOut);
	if (m_hasXRotation) {
		p->set3dRotation(m_xRotSpeed);
	}
	
	//添加粒子
	if (isTex) {
		ParticleMaster::addParticle(*p);
	}
	else {
		ParticleMaster::addColourPartivle(*p, m_additive);
	}

	delete p;
}




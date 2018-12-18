#include "particle.h"


//TODO:需要手动添加到粒子列表中
//TODO:deltatime的获取方法没有确定

Particle::Particle(ParticleTexture texture, vec3 position, vec3 velocity,
	float gravityEffect, float lifeLength, float rotation, float scale) {
	m_texture = texture;	//TODO:顶一个复制函数
	m_position = position;
	m_velocity = velocity;
	m_gravityEffect = gravityEffect;
	m_lifeLength = lifeLength;
	m_rotation = rotation;
	m_scale = scale;
	//ParticleMaster.addParticle(this);
}

Particle::Particle(Color colour, bool additive, vec3 position, vec3 velocity,
	float gravityEffec, float lifeLength, float rotation, float scale) {
	m_color = colour;
	m_position = position;
	m_velocity = velocity;
	m_gravityEffect = gravityEffec;
	m_lifeLength = lifeLength;
	m_rotation = rotation;
	m_scale = scale;
	//ParticleMaster.addColourParticle(this, additive);
}

Particle::Particle(ParticleTexture texture, vec3 position, float scale, float deathAnimationTime) {
	m_texture = texture;
	m_position = position;
	m_scale = scale;
	m_lifeLength = deathAnimationTime;
	m_rotation = 0;
	m_gravityEffect = 0;
	//ParticleMaster.addParticle(this);
}

Particle::Particle(ParticleTexture texture, float scale, float deathAnimationTime,
	Transformation transform, float heightOffset) {
	m_texture = texture;
	m_scale = scale;
	m_lifeLength = deathAnimationTime;
	*m_parent = transform;
	m_heightOffset = heightOffset;
	m_rotation = 0;
	m_gravityEffect = 0;
	//ParticleMaster.addParticle(this);
}


//TODO：没有设计好
bool Particle::update(Camera camera, float deltaTime) {
	if (m_parent == nullptr) {
		moveParticleNaturally(deltaTime);
	}
	else{
		followParent();
	}

	rotate(deltaTime);


	return true;
}

float Particle::getTransparency() {

	//时间流逝百分比
	float lightFactor = m_elapsedTime / m_lifeLength;

	if (lightFactor < m_fadeIn) {//还没有完全显示
		float factor = lightFactor / m_fadeIn;
		return factor * m_normalAlpha;
	}
	else if (lightFactor > m_fadeOut) {//已经完全显示开始消失透明
		float factor = 1 - (lightFactor - m_fadeOut) / (1 - m_fadeOut);
		return factor * m_normalAlpha;
	}
	else {//其余时候完全显示
		return 1;
	}
}

void Particle::moveParticleNaturally(float deltaTime){//自由落体
	//受到重力影响 y轴的速度朝重力方向变化
	m_velocity.y += EnvironmentVariables::GRAVITY * m_gravityEffect * deltaTime;

	//计算移动后的位置
	m_position.x += m_velocity.x * deltaTime;
	m_position.y += m_velocity.y * deltaTime;
	m_position.z += m_velocity.z * deltaTime;

}

void Particle::rotate(float deltaTime) {
	if (m_rotate3D) {
		m_rotX += deltaTime * m_rotXSpeed;
	}
}

void Particle::followParent() {
	//TODO:需要transformation
}


//粒子的贴图为n*n的纹理贴图，每次取其中的一个小块，更新取得坐标
void Particle::updateTextureCoordInfo() {
	float lifeFactor = m_elapsedTime / m_lifeLength; 
	int stageCount = m_texture.getNumberOfRows() * m_texture.getNumberOfRows();//总纹理数
	float atlasProgression = lifeFactor * stageCount;//现在对应纹理
	int index1 = floor(atlasProgression);//向下取整
	int index2 = index1 < atlasProgression ? index1 + 1 : index1;
	m_blend = fmod(atlasProgression, 1);
	setTextureOffset(m_texOffset1, index1);
	setTextureOffset(m_texOffset2, index2);
}

//计算出当前粒子对于材质小块的左上角坐标
void Particle::setTextureOffset(vec2 & offset, int index) {
	int column = index % m_texture.getNumberOfRows();
	int row = index / m_texture.getNumberOfRows();
	offset.x = (float)column / m_texture.getNumberOfRows();
	offset.y = (float)row / m_texture.getNumberOfRows();
}
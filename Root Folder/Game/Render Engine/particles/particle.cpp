#include "particle.h"
#include "../basics/displaymanager.h"


//TODO:需要手动添加到粒子列表中


Particle::Particle(ParticleTexture texture, vec3 position, vec3 velocity,
	float gravityEffect, float lifeLength, float rotation, float scale) {
	m_Texture = texture;	
	m_Position = position;
	m_Velocity = velocity;
	m_GravityEffect = gravityEffect;
	m_LifeLength = lifeLength;
	m_Rotation = rotation;
	m_Scale = scale;
	//ParticleMaster.addParticle(this);
}

Particle::Particle(ParticleTexture texture, vec3 position, float scale, float deathAnimationTime) {
	m_Texture = texture;
	m_Position = position;
	m_Scale = scale;
	m_LifeLength = deathAnimationTime;
	m_Rotation = 0;
	m_GravityEffect = 0;
	//ParticleMaster.addParticle(this);
}

Particle::Particle(ParticleTexture texture, float scale, float deathAnimationTime,
	Transformation transform, float heightOffset) {
	m_Texture = texture;
	m_Scale = scale;
	m_LifeLength = deathAnimationTime;
	m_HeightOffset = heightOffset;
	m_Rotation = 0;
	m_GravityEffect = 0;
	//TODO:tansform没有
	//ParticleMaster.addParticle(this);
}

Particle::Particle(Color colour, bool additive, vec3 position, vec3 velocity,
	float gravityEffec, float lifeLength, float rotation, float scale) {
	m_Color = colour;
	m_Position = position;
	m_Velocity = velocity;
	m_GravityEffect = gravityEffec;
	m_LifeLength = lifeLength;
	m_Rotation = rotation;
	m_Scale = scale;
	m_IsColor = true;
	//ParticleMaster.addColourParticle(this, additive);
}


//TODO：没有设计好
bool Particle::update(Camera camera) {
	if (m_Parent == nullptr) {
		moveParticleNaturally();
	}
	else{
		followParent();
	}
	rotate();
	if (!m_IsColor && !m_ManualStages) {
		updateTextureCoordInfo();
	}
	vec3 vdistance = m_Position - camera.getPosition();
	m_Distance =
		vdistance.x * vdistance.x +
		vdistance.y * vdistance.y +
		vdistance.z * vdistance.z;
	if (m_Decays) {
		//TODO：临时用getDelta代替，后面再替换成对应的值
		m_ElapsedTime += DisplayManager::getDelta();
	}
	//不需要透明变化返回真
	//还没有显示完返回真
	return !m_Decays || m_ElapsedTime < m_LifeLength;
}

float Particle::getTransparency() {

	//时间流逝百分比
	float lightFactor = m_ElapsedTime / m_LifeLength;

	if (lightFactor < m_FadeIn) {//还没有完全显示
		float factor = lightFactor / m_FadeIn;
		return factor * m_NormalAlpha;
	}
	else if (lightFactor > m_FadeOut) {//已经完全显示开始消失透明
		float factor = 1 - (lightFactor - m_FadeOut) / (1 - m_FadeOut);
		return factor * m_NormalAlpha;
	}
	else {//其余时候完全显示
		return 1;
	}
}

void Particle::moveParticleNaturally(){//自由落体
	//受到重力影响 y轴的速度朝重力方向变化
	m_Velocity.y += EnvironmentVariables::GRAVITY * m_GravityEffect * DisplayManager::getDelta();

	//计算移动后的位置
	//TODO：临时用getDelta代替，后面再替换成对应的值
	m_Position.x += m_Velocity.x * DisplayManager::getDelta();
	m_Position.y += m_Velocity.y * DisplayManager::getDelta();
	m_Position.z += m_Velocity.z * DisplayManager::getDelta();

}

void Particle::rotate() {
	if (m_Rotate3D) {
		m_RotX += DisplayManager::getDelta() * m_RotXSpeed;
	}
}

void Particle::followParent() {
	//TODO:没有实现，需要transformation
}


//粒子的贴图为n*n的纹理贴图，每次取其中的一个小块，更新取得坐标
void Particle::updateTextureCoordInfo() {
	float lifeFactor = m_ElapsedTime / m_LifeLength; 

	//printf(" m_elapsedTime = %f ,m_LifeLength = %f , lifeFactor = %f\n", m_elapsedTime, m_LifeLength, lifeFactor);

	if (lifeFactor >= 1.0f) {
		m_ElapsedTime = 0;
	}
	int stageCount = m_Texture.getNumberOfRows() * m_Texture.getNumberOfRows();//总纹理数
	float atlasProgression = lifeFactor * stageCount;//现在对应纹理
	int index1 = floor(atlasProgression);//向下取整
	int index2 = index1 < stageCount - 1 ? index1 + 1 : index1;
	m_Blend = fmod(atlasProgression, 1);
	setTextureOffset(m_TexOffset1, index1);
	setTextureOffset(m_TexOffset2, index2);
}

//计算出当前粒子对于材质小块的左上角坐标
void Particle::setTextureOffset(vec2 & offset, int index) {
	int column = index % m_Texture.getNumberOfRows();
	int row = index / m_Texture.getNumberOfRows();
	offset.x = (float)column / m_Texture.getNumberOfRows();
	offset.y = (float)row / m_Texture.getNumberOfRows();
}
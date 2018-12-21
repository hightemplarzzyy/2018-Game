#ifndef _PARTICLES_H_
#define _PARTICLES_H_

#include "../toolbox/maths/maths_func.h"
#include "../toolbox/Color.h"
#include "../toolbox/Transformation.h"
#include "../../Source/main/camera.h"
#include "../environment/environment.h"


#include "ParticleTexture.h"



class Particle {
private:
	//粒子基本属性
	vec3 m_position;
	vec3 m_velocity;
	float m_gravityEffect;
	float m_lifeLength;				//总的时间
	float m_rotation;
	float m_scale;

	//显示效果：透明------显示------------显示-----透明
	//时间轴：-----------m_fadeIn-------m_fadeOut------
	float m_fadeIn = 0;				//从开始透明到完全显示的时刻(百分比）0~1
	float m_fadeOut = 1;			//从完全显示到开始透明的时刻(百分比）0~1
	float m_normalAlpha = 1;		//标准透明度
	
	Color m_color;
	bool m_isColor = false;

	bool m_rotate3D = false;
	float m_rotX = 0;
	float m_rotXSpeed = 0;

	float m_elapsedTime =0 ;		//已经过去的时间

	ParticleTexture m_texture;

	vec2 m_texOffset1;
	vec2 m_texOffset2;
	float m_blend;
	float m_distance;
	bool m_manualStages = false;

	bool m_decays = true;			//衰减度
	
	//TODO：没有做
	Transformation * m_parent= nullptr;		

	float m_heightOffset = 0;

public:
	Particle() = default;
	//纹理类粒子
	Particle(ParticleTexture texture, vec3 position, vec3 velocity, float gravityEffect,
		float lifeLength, float rotation, float scale);
	//纹理类粒子
	Particle(ParticleTexture texture, vec3 position, float scale, float deathAnimationTime);
	//纹理类粒子
	Particle(ParticleTexture texture, float scale, float deathAnimationTime, Transformation transform,
		float heightOffset);
	//颜色类粒子
	Particle(Color colour, bool additive, vec3 position, vec3 velocity, float gravityEffec,
		float lifeLength, float rotation, float scale);

	void setHeighOffset(float offset) {
		m_heightOffset = offset; 
	}

	void set3dRotation(float speed) {
		m_rotate3D = true;
		m_rotX = rand() % 360;
		m_rotXSpeed = speed;
	}

	void setPosition(vec3 pos) {
		m_position = pos;
	}

	void kill() {
		m_decays = true;
	}

	void setFade(float normalAlpha, float fadeIn, float fadeOut) {
		m_normalAlpha = normalAlpha;
		m_fadeIn = fadeIn;
		m_fadeOut = fadeOut;
	}

	void setManualStage(bool manual) {
		m_manualStages = manual;
	}

	void setStage(int index) {
		m_manualStages = true;
		setTextureOffset(m_texOffset1, index);
		setTextureOffset(m_texOffset2, index);
	}

	void setStages(int preIndex, int nextIndex, float blend) {
		m_manualStages = true;
		setTextureOffset(m_texOffset1, preIndex);
		setTextureOffset(m_texOffset2, nextIndex);
		m_blend = blend;
	}

	Color getColour() {
		return m_color;
	}

	float getDistance() {
		return m_distance;
	}

	vec2 getTexOffset1() {
		return m_texOffset1;
	}

	vec2 getTexOffset2() {
		return m_texOffset2;
	}

	float getBlend() {
		return m_blend;
	}

	ParticleTexture getTexture() {
		return m_texture;
	}

	vec3 getPosition() {
		return m_position;
	}

	float getRotation() {
		return m_rotation;
	}

	float getRotX() {
		return m_rotX;
	}

	float getScale() {
		return m_scale;
	}

	bool update(Camera camera);

	//计算透明度
	//随着流逝时间粒子的透明度不断变化
	float getTransparency();

private:
	void moveParticleNaturally();
	void rotate();
	void followParent();
	void updateTextureCoordInfo();
	void setTextureOffset(vec2 & offset, int index);
	//TODO：添加添加粒子的方法
	
};


#endif // _PARTICLES_H_

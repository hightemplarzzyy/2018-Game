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
	vec3 m_Position;
	vec3 m_Velocity;
	float m_GravityEffect;
	float m_LifeLength;				//总的时间
	float m_Rotation;
	float m_Scale;

	//显示效果：透明------显示------------显示-----透明
	//时间轴：-----------m_fadeIn-------m_fadeOut------
	float m_FadeIn = 0;				//从开始透明到完全显示的时刻(百分比）0~1
	float m_FadeOut = 1;			//从完全显示到开始透明的时刻(百分比）0~1
	float m_NormalAlpha = 1;		//标准透明度
	
	Color m_Color;
	bool m_IsColor = false;

	bool m_Rotate3D = false;
	float m_RotX = 0;
	float m_RotXSpeed = 0;

	float m_ElapsedTime =0 ;		//已经过去的时间

	ParticleTexture m_Texture;

	vec2 m_TexOffset1;
	vec2 m_TexOffset2;
	float m_Blend;
	float m_Distance;
	bool m_ManualStages = false;

	bool m_Decays = true;			//衰减度
	
	//TODO：没有做
	Transformation * m_Parent= nullptr;		

	float m_HeightOffset = 0;

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
		m_HeightOffset = offset; 
	}

	void set3dRotation(float speed) {
		m_Rotate3D = true;

		m_RotX = float(rand() % 360);

		m_RotXSpeed = speed;
	}

	void setPosition(vec3 pos) {
		m_Position = pos;
	}

	void kill() {
		m_Decays = true;
	}

	void setFade(float normalAlpha, float fadeIn, float fadeOut) {
		m_NormalAlpha = normalAlpha;
		m_FadeIn = fadeIn;
		m_FadeOut = fadeOut;
	}

	void setManualStage(bool manual) {
		m_ManualStages = manual;
	}

	void setStage(int index) {
		m_ManualStages = true;
		setTextureOffset(m_TexOffset1, index);
		setTextureOffset(m_TexOffset2, index);
	}

	void setStages(int preIndex, int nextIndex, float blend) {
		m_ManualStages = true;
		setTextureOffset(m_TexOffset1, preIndex);
		setTextureOffset(m_TexOffset2, nextIndex);
		m_Blend = blend;
	}

	Color getColour() {
		return m_Color;
	}

	float getDistance() {
		return m_Distance;
	}

	vec2 getTexOffset1() {
		return m_TexOffset1;
	}

	vec2 getTexOffset2() {
		return m_TexOffset2;
	}

	float getBlend() {
		return m_Blend;
	}

	ParticleTexture getTexture() {
		return m_Texture;
	}

	vec3 getPosition() {
		return m_Position;
	}

	float getRotation() {
		return m_Rotation;
	}

	float getRotX() {
		return m_RotX;
	}

	float getScale() {
		return m_Scale;
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

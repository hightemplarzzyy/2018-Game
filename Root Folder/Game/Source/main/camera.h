#pragma once

#include "../../Render Engine/toolbox/maths/maths_func.h"
#include "../../Render Engine/basics/DIsplayManager.h"

class Camera {
private:
	vec3 m_Move = vec3();						//相机移动向量
	vec3 m_Target;								//相机焦点
	vec3 m_Offset;								//相机和目标之间偏移
	vec3 m_Front;								//相机面向，y=0
	vec3 m_Up;									//相机上向量
	vec3 m_Right;								//相机右向量
	vec3 m_WorldUp = vec3(0.0f, 1.0f, 0.0f);	//世界上向量

	GLfloat m_Speed = 10.0f;		//相机速度
	GLfloat m_Sensitivity = 5.0f;	//相机旋转敏感度
	GLfloat m_Yaw = 0.0f;			//绕Y轴
	GLfloat m_Pitch = 0.0f;			//绕X轴
	GLfloat m_Omission = 2.0f;		//滤除抖动

	float m_Distance;
	float m_DisDelta = 0.0f;

	bool m_isFirst = true;
	float m_preX = DisplayManager::getScreenWidth() / 2;
	float m_preY = DisplayManager::getScreenHeigh() / 2;

private:
	void vectorUpdate();
	void processKeyboard();
	void processMouseMovenment(GLfloat xoffset, GLfloat yoffset);
	void processMouseRotate(GLfloat xoffset, GLfloat yoffset);
	void processMouseScroll();

	static mat4 lookAt(const vec3 & cameraPos, const vec3 & cameraTarget, const vec3 & cameraUp);

public:
	Camera(vec3 Target, vec3 Position);
	float getAimDistance();
	void move();
	vec3 getPosition();
	vec3 getTargetPosition();
	mat4 CreateViewMatrix();

	//static Camera & getCamera();
};
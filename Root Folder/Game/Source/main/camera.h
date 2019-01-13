#pragma once

#include "../../Render Engine/toolbox/maths/maths_func.h"
#include "../../Render Engine/basics/DIsplayManager.h"

class Camera {
private:
	vec3 m_Move = vec3();						//����ƶ�����
	vec3 m_Target;								//�������
	vec3 m_Offset;								//�����Ŀ��֮��ƫ��
	vec3 m_Front;								//�������y=0
	vec3 m_Up;									//���������
	vec3 m_Right;								//���������
	vec3 m_WorldUp = vec3(0.0f, 1.0f, 0.0f);	//����������

	GLfloat m_Speed = 10.0f;		//����ٶ�
	GLfloat m_Sensitivity = 5.0f;	//�����ת���ж�
	GLfloat m_Yaw = 0.0f;			//��Y��
	GLfloat m_Pitch = 0.0f;			//��X��
	GLfloat m_Omission = 2.0f;		//�˳�����

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
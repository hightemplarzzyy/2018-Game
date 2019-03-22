#pragma once

#include "../../Render Engine/toolbox/maths/maths_func.h"
#include "../../Render Engine/basics/window.h"


class Camera {
private:
	vec3 m_Position;
	float m_Pitch;
	float m_Yaw;
	Window *m_Window;
	float m_Near;
	float m_Far;
	float m_Fov;
	mat4 m_ViewMatrix;

public:
	Camera(Window *w) {
		m_Window = w;
		m_Near = 0.15f;
		m_Far = 2000.0f;
		m_Fov = 35.0f;
		m_Position.x = m_Position.y = m_Position.z = m_Pitch = m_Yaw = 0.0f;
	};

	void move() {
		if (m_Window->isKeyPressed(87)) {
			m_Position.z += 0.02f;
		}
		if (m_Window->isKeyPressed(83)) {
			m_Position.z -= 0.02f;
		}
		if (m_Window->isKeyPressed(68)) {
			m_Position.x += 0.02f;
		}
		if (m_Window->isKeyPressed(65)) {
			m_Position.x -= 0.02f;
		}
		if (m_Window->isKeyPressed(340)) {
			m_Position.y += 0.02f;
		}
		if (m_Window->isKeyPressed(341)) {
			m_Position.y -= 0.02f;
		}
		if (m_Window->isKeyPressed(81)) {
			m_Yaw -= 0.6f;
		}
		if (m_Window->isKeyPressed(69)) {
			m_Yaw += 0.6f;
		}
	};

	vec3 getPosition() {
		return vec3();
	}

	float getNearPlane() {
		return m_Near;
	};

	float getFarPlane() {
		return m_Far;
	};

	float getFOV() {
		return m_Fov;
	};

	mat4 getViewMatrix() {
		m_ViewMatrix = CreateViewMatrix();
		return m_ViewMatrix;
	};

	void reflect(float waterHeight) {
		m_Position.y -= 2 * (m_Position.y - waterHeight);
		m_Pitch = -m_Pitch;
	};

	float getPitch() {
		return m_Pitch;
	};

	float getYaw() {
		return m_Yaw;
	};

	mat4 CreateViewMatrix() {
		mat4 view_matrix(1.0);
		view_matrix *= (mat4::rotation(m_Pitch, vec3(1.0, 0.0, 0.0)));
		view_matrix *= (mat4::rotation(m_Yaw, vec3(0.0, 1.0, 0.0)));
		view_matrix *= (mat4::translation(vec3(-m_Position.x, -m_Position.y, -m_Position.z)));
		return view_matrix;
	}
};
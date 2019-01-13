#include "camera.h"

Camera::Camera(vec3 Target, vec3 Position) {
	m_Target = Target;
	m_Offset = Position - Target;
	m_Distance = m_Offset.length();
	m_Offset.normalize();
	m_Front = vec3(-m_Offset.x, 0.0f, -m_Offset.z);
	m_Front.normalize();
}

void Camera::vectorUpdate() {
	vec3 t_front = m_Front * mat4::rotation(m_Yaw, m_WorldUp);
	m_Right = cross(t_front, m_WorldUp);
	m_Right.normalize();
	m_Up = cross(m_Right, t_front);
	m_Up.normalize();
}

vec3 Camera::getPosition() {
	return m_Target + m_Move 
		+ (m_Offset * getAimDistance()) * mat4::rotation(m_Yaw, m_WorldUp) * mat4::rotation(m_Pitch, m_Right);
}

vec3 Camera::getTargetPosition() {
	return m_Target + m_Move;
}

mat4 Camera::CreateViewMatrix() {
	return lookAt(getPosition(), getTargetPosition(), m_Up);
}

float Camera::getAimDistance() {
	return m_Distance + m_DisDelta;
}

void Camera::processKeyboard() {

	float velocity = m_Speed * DisplayManager::getDelta();

	if (DisplayManager::isKeyPressed(GLFW_KEY_W)) {
		m_Move += m_Front * mat4::rotation(m_Yaw, m_WorldUp) * velocity;
	}
	if (DisplayManager::isKeyPressed(GLFW_KEY_S)) {
		m_Move -= m_Front * mat4::rotation(m_Yaw, m_WorldUp) * velocity;
	}
	if (DisplayManager::isKeyPressed(GLFW_KEY_A)) {
		m_Move -= m_Right * velocity;
	}
	if (DisplayManager::isKeyPressed(GLFW_KEY_D)) {
		m_Move += m_Right * velocity;
	}
	if (DisplayManager::isKeyPressed(GLFW_KEY_Q)) {
		m_Yaw += velocity * m_Sensitivity;
	}
	if (DisplayManager::isKeyPressed(GLFW_KEY_E)) {
		m_Yaw -= velocity * m_Sensitivity;
	}
	if (DisplayManager::isKeyPressed(GLFW_KEY_Z)) {
		m_Pitch += velocity * m_Sensitivity;
	}
	if (DisplayManager::isKeyPressed(GLFW_KEY_C)) {
		m_Pitch -= velocity * m_Sensitivity;
	}

	if (m_Pitch > 30.0f) {
		m_Pitch = 30.0f;
	}
	if (m_Pitch < -40.0f) {
		m_Pitch = -40.0f;
	}
}

void Camera::processMouseMovenment(GLfloat xoffset, GLfloat yoffset) {
	GLfloat velocity = m_Speed * DisplayManager::getDelta();

	if (xoffset < -m_Omission) {
		m_Move += m_Right * velocity;
	}
	if (xoffset > m_Omission) {
		m_Move -= m_Right * velocity;
	}
	if (yoffset < -m_Omission) {
		m_Move -= m_Up * velocity;
	}
	if (yoffset > m_Omission) {
		m_Move += m_Up * velocity;
	}

}

void Camera::processMouseRotate(GLfloat xoffset, GLfloat yoffset) {
	GLfloat velocity = m_Speed * DisplayManager::getDelta() * m_Sensitivity * m_Sensitivity;

	if (xoffset < -m_Omission) {
		m_Yaw += velocity;
	}
	if (xoffset > m_Omission) {
		m_Yaw -= velocity;
	}
	if (yoffset < -m_Omission) {
		m_Pitch += velocity;
	}
	if (yoffset > m_Omission) {
		m_Pitch -= velocity;
	}

	if (m_Pitch > 30.0f) {
		m_Pitch = 30.0f;
	}
	if (m_Pitch < -20.0f) {
		m_Pitch = -20.0f;
	}
}

void Camera::processMouseScroll() {
	m_DisDelta = DisplayManager::window->getDisDelta();
}

void Camera::move() {

	//键盘处理
	processKeyboard();

	//处理鼠标
	if (DisplayManager::isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)
		|| DisplayManager::isMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE)) {
		double nowPosX, nowPosY;
		GLfloat gl_nowPosX, gl_nowPosY;
		DisplayManager::getMousePosition(nowPosX, nowPosY);
		gl_nowPosX = (GLfloat)nowPosX;
		gl_nowPosY = (GLfloat)nowPosY;
		GLfloat xoffet = gl_nowPosX - m_preX;
		GLfloat yoffet = gl_nowPosY - m_preY;
		m_preX = gl_nowPosX;
		m_preY = gl_nowPosY;
		if (m_isFirst) {
			xoffet = 0;
			yoffet = 0;
			m_isFirst = false;
		}
		if (DisplayManager::isMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE)) {
			processMouseRotate(xoffet, yoffet);
		}
		if (DisplayManager::isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
			processMouseMovenment(xoffet, yoffet);
		}
	}

	//处理滚轮
	processMouseScroll();

	vectorUpdate();
}

mat4  Camera::lookAt(const vec3 & cameraPos, const vec3 & cameraTarget, const vec3 & cameraUp) {

	vec3 Direction = cameraPos - cameraTarget;
	Direction.normalize();
	vec3 Right = cross(cameraUp, Direction);
	Right.normalize();
	vec3 Up = cross(Direction, Right);

	mat4 ans = mat4(1);

	ans.elements[4 * 0 + 0] = Right.x;
	ans.elements[4 * 1 + 0] = Right.y;
	ans.elements[4 * 2 + 0] = Right.z;

	ans.elements[4 * 0 + 1] = Up.x;
	ans.elements[4 * 1 + 1] = Up.y;
	ans.elements[4 * 2 + 1] = Up.z;

	ans.elements[4 * 0 + 2] = Direction.x;
	ans.elements[4 * 1 + 2] = Direction.y;
	ans.elements[4 * 2 + 2] = Direction.z;

	vec3 dot = Right * cameraPos;
	ans.elements[4 * 3 + 0] = -(dot.x + dot.y + dot.z);
	dot = Up * cameraPos;
	ans.elements[4 * 3 + 1] = -(dot.x + dot.y + dot.z);
	dot = Direction * cameraPos;
	ans.elements[4 * 3 + 2] = -(dot.x + dot.y + dot.z);

	return ans;
}

//Camera & Camera::getCamera() {
//	static Camera  * camear;
//	if (camear == nullptr) {
//		camear = new Camera(vec3(0, 0, 0), vec3(-10, 10, 10));
//	}
//	return *camear;
//}
#include <iostream>

#include "window.h"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
void window_resize(GLFWwindow *window, int width, int height);
void scroll_callback(GLFWwindow *Window, double xoffset, double yoffet);
void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar *message,
	const void *userParam);

Window::Window(const char * title,int width,int height) {
	m_Title = title;
	m_Width = width;
	m_Height = height;

	if (!init())
		glfwTerminate();

	for (int i = 0; i < MAX_KEYS; i++)
		m_Keys[i] = false;
	for (int i = 0; i < MAX_BUTTONS; i++)
		m_MouseButtons[i] = false;

	
}

Window::~Window() {
		glfwTerminate();
}

bool Window::closed() const{
		return glfwWindowShouldClose(m_Window);
}

void Window::update(){
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		std::cout << "OpenGL Error: " << error << std::endl;

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void Window::clear() const {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::isKeyPressed(unsigned int keycode) const {
	if (keycode >= MAX_KEYS)
		return false;
	return m_Keys[keycode];
}

bool Window::isMouseButtonPressed(unsigned int button) const {
	if (button >= MAX_BUTTONS)
		return false;
	return m_MouseButtons[button];
}

void Window::getMousePosition(double &x, double &y) const {
	x = m_X;
	y = m_Y;
}

bool Window::init() {
	if (!glfwInit())
		return false;

	
#ifdef _DEBUG
	//初始化回调上下文
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
	

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	glfwMakeContextCurrent(m_Window);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowUserPointer(m_Window,this);
	glfwSetFramebufferSizeCallback(m_Window, window_resize);
	glfwSetKeyCallback(m_Window, key_callback);
	glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
	glfwSetCursorPosCallback(m_Window, cursor_position_callback);
	glfwSetScrollCallback(m_Window, scroll_callback);
	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW fail" << std::endl;
		return false;
	}

#ifdef _DEBUG	
	//打印错误信息，只在DEBUG模式下面有效
	GLint flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		// 初始化调试输出
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DEBUG_SOURCE_API,
			GL_DEBUG_TYPE_ERROR,
			GL_DEBUG_SEVERITY_HIGH,
			0, nullptr, GL_TRUE);
	}
#endif

	std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
	return true;
}

//只有再窗口大小改变的时候才会执行
void window_resize(GLFWwindow *window, int width, int height) {
	Window *win = (Window*)glfwGetWindowUserPointer(window);
	win->m_Width = width;
	win->m_Height = height;
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	Window *win = (Window*)glfwGetWindowUserPointer(window);
	win->m_Keys[key] = action != GLFW_RELEASE;
	//std::cout << "keyboard " << '"' << key << '"' << " Pressed!" << std::endl;
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
	Window *win = (Window*)glfwGetWindowUserPointer(window);
	win->m_MouseButtons[button] = action != GLFW_RELEASE;
	//std::cout << "mouse " << '"' << button << '"' << " Pressed!" << std::endl;
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
	Window *win = (Window*)glfwGetWindowUserPointer(window);
	win->m_X = xpos;
	win->m_Y = ypos;
	//std::cout << "x: " << xpos << " y: " << ypos << std::endl;
}

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset) {
	Window * win = (Window*)glfwGetWindowUserPointer(window);
	if (win->m_DisDelta >= -30.0f && win->m_DisDelta <= 40.0f) {
		win->m_DisDelta -= yoffset;
	}
	if (win->m_DisDelta < -30.0f) {
		win->m_DisDelta = -30.0f;
	}
	if (win->m_DisDelta > 40.0f) {
		win->m_DisDelta = 40.0f;
	}
}


void GLAPIENTRY glDebugOutput(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar *message,
	const void *userParam)
{
	// 忽略一些不重要的错误/警告代码
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}
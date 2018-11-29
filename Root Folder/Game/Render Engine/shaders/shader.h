#pragma once

#include <iostream>
#include <GL/glew.h>
#include <vector>

#include "../toolbox/maths/maths_func.h"
#include "../../Resource Management/utils/fileutils.h"

class Shader {
private:
	GLuint m_ShaderID;
	const char *m_VertPath, *m_FragPath;
	
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void setUniform1f(const GLchar * name, float value);
	void setUniform1i(const GLchar * name, int value);
	void setUniform2f(const GLchar * name, const vec2 &v);
	void setUniform3f(const GLchar * name, const vec3 &v);
	void setUniform4f(const GLchar * name, const vec4 &v);

	void setUniformMat4(const GLchar * name, const mat4 &matrix);

	void enable() const;
	void disable() const;

	GLuint getID();
private:
	GLuint load();
	GLint getUniformLocation(const GLchar *name);
};
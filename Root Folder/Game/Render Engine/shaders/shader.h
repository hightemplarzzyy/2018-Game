#pragma once

#include <iostream>
#include <GL/glew.h>
#include <vector>

#include "../toolbox/maths/maths_func.h"
#include "../../Resource Management/utils/fileutils.h"

class Shader {
protected:
	GLuint m_ShaderID;
	const char *m_VertPath, *m_FragPath;
	
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	virtual void storeAllUniformLocation() = 0;
	void enable() const;
	void disable() const;

	GLuint getID();
private:
	GLuint createShader();
};
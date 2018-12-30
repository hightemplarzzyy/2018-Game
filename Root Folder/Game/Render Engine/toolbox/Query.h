#pragma once

#include <GL/glew.h>

//ÕÚµ²²éÑ¯
class Query {

private:
	GLuint m_id;
	GLenum m_type;

	bool m_inUse = false;

public:
	Query(GLenum  type) {
		glGenQueries(1, &m_id);
		m_type = type;
	}

	void start() {
		m_inUse = true;
		glBeginQuery(m_type, m_id);
	}

	void end() {
		glEndQuery(m_type);
	}

	bool isResultReady() {
		GLint result;
		glGetQueryObjectiv(m_id, GL_QUERY_RESULT_AVAILABLE, &result);
		return result == GL_TRUE;
	}

	bool isInUse() {
		return m_inUse;
	}

	int getResult() {
		m_inUse = false;
		GLint result;
		glGetQueryObjectiv(m_id, GL_QUERY_RESULT, &result);
		return result;
	}

	void delte() {
		glDeleteQueries(1,&m_id);
	}
};
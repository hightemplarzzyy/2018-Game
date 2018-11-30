#pragma once

#include <string>
#include <GL/glew.h>

class Uniform {
public:
	int m_Location;
	std::string m_Name;
	Uniform(std::string name) :m_Name(name) {};

	void storeLocation(int id) {
		m_Location = glGetUniformLocation(id, m_Name.c_str());
	};
};
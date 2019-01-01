#ifndef _PARTICLES_COLOUR_SHADER_H_
#define _PARTICLES_COLOUR_SHADER_H_

#include "../shaders/shader.h"
#include "../shaders/uniformmat4.h"
#include "../shaders/uniformvec3.h"

//É«¿éµÄÁ£×Ó
class ParticleColourShader :public Shader {
public:
	UniformMat4 * projection_matrix = new UniformMat4("projection_matrix");
	UniformVec3 * light_colour = new UniformVec3("light_colour");
	UniformVec3 * light_colour = new UniformVec3("light_position");

	ParticleColourShader(const char * vertexPath, const char * fragmentPath) :
		Shader(vertexPath, fragmentPath) {
		storeAllUniformLocation();
	}

	virtual void storeAllUniformLocation() {
		projection_matrix->storeLocation(m_ShaderID);
		light_colour->storeLocation(m_ShaderID);
	}
};

#endif // !_PARTICLES_COLOUR_SHADER_H_

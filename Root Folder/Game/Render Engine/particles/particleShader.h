#ifndef _PARTICLES_SHADER_H_
#define _PARTICLES_SHADER_H_

#include "../shaders/shader.h"
#include "../shaders/uniformmat4.h"
#include "../shaders/uniform1f.h"
#include "../shaders/uniformvec3.h"

//带有纹理的粒子
class ParticleShader: public Shader{
public:
	UniformMat4 * projection_matrix = new UniformMat4("projection_matrix");
	Uniform1f * numberOfRaws = new Uniform1f("numberOfRows");
	UniformVec3 * light_colour = new UniformVec3("light_colour");

	ParticleShader(const char * vertexPath, const char * fragmentPath) :
		Shader(vertexPath, fragmentPath) {
		storeAllUniformLocation();
	}

	virtual void storeAllUniformLocation() {
		projection_matrix->storeLocation(m_ShaderID);
		light_colour->storeLocation(m_ShaderID);
		numberOfRaws->storeLocation(m_ShaderID);
	}
};
#endif // !_PARTICLES_SHADER_H_

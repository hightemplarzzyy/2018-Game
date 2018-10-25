#include <iostream>

#include "Source/graphics/window.h"
#include "Source/maths/maths_func.h"
#include "Source/graphics/shader.h"
#include "Source/graphics/buffers/buffer.h"
#include "Source/graphics/buffers/indexbuffer.h"
#include "Source/graphics/buffers/vertexarray.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

using namespace std;
int main() {
	Window window("Game", WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

#if 0
	GLfloat vertices[] = {
		0, 0, 0,
		8, 0, 0,
		0, 3, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0
	};
	GLfloat colors[] = {
	0.2f, 0.3f, 0.8f, 1.0f,
	0.2f, 0.3f, 0.8f, 1.0f,
	0.2f, 0.3f, 0.8f, 1.0f,
	0.2f, 0.3f, 0.8f, 1.0f,
	0.2f, 0.3f, 0.8f, 1.0f,
	0.2f, 0.3f, 0.8f, 1.0f
	};

	VertexArray vao1;
	vao1.addBuffer(new Buffer(vertices, 6 * 3, 3), 0);
	vao1.addBuffer(new Buffer(colors, 6 * 4, 4), 1);

#else
	GLfloat vertices[] = {
	0, 0, 0,
	0, 3, 0,
	8, 3, 0,
	8, 0, 0
	};

	GLushort indicies[] = {
		0,1,2,
		2,3,0
	};

	GLfloat colorsA[] = {
		1,0,1,1,
		1,0,1,1,
		1,0,1,1,
		1,0,1,1
	};

	GLfloat colorsB[] = {
		0.2f, 0.3f, 0.8f, 1.0f,
		0.2f, 0.3f, 0.8f, 1.0f,
		0.2f, 0.3f, 0.8f, 1.0f,
		0.2f, 0.3f, 0.8f, 1.0f
	};

	VertexArray vao1,vao2;
	IndexBuffer ibo(indicies, 6);
	
	vao1.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	vao1.addBuffer(new Buffer(colorsA, 4 * 4, 4), 1);

	vao2.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	vao2.addBuffer(new Buffer(colorsB, 4 * 4, 4), 1);

#endif 
	Shader shader("source/shaders/basic.vert", "source/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("projection_matrix", mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	shader.setUniformMat4("model_matrix", mat4::translation(vec3(4, 3, 0)));
	shader.setUniform2f("light_position", vec2(8.0,4.5));


	while (!window.closed()) {
		
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_position", vec2((float)(x * 16.0f / (float)WINDOW_WIDTH), (float)(9.0f - y * 9.0f / (float)WINDOW_HEIGHT)));
#if 0
		vao1.bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		vao1.unbind();
#else

		vao1.bind(); 
		ibo.bind();
		shader.setUniformMat4("model_matrix", mat4::translation(vec3(4, 3, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		vao1.unbind();

		vao2.bind();
		ibo.bind();
		shader.setUniformMat4("model_matrix", mat4::translation(vec3(0.0f, 0.0f, 0.0f)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		vao2.unbind();
#endif
		window.update();
	}
	
	return 0;
}
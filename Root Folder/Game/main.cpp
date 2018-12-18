#include <iostream>

#include <vector>

#include "Render Engine/basics/window.h"
#include "Render Engine/toolbox/maths/maths_func.h"
#include "Render Engine/shaders/dragonshader.h"
#include "Render Engine/buffers/buffer.h"
#include "Render Engine/buffers/indexbuffer.h"
#include "Render Engine/buffers/vertexarray.h"
#include "Render Engine/textures/texture.h"
#include "Source/entity/models.h"
#include "Source/main/camera.h"
#include "Render Engine/postProcessing/GaussianBlur/GaussianBlur.h"
#include "Render Engine/postProcessing/InvertColor/InvertColor.h"
#include "Render Engine/basics/terrain.h"
#include "Render Engine/basics/terrainShader.h"


#define WINDOW_WIDTH 1920	
#define WINDOW_HEIGHT 1080


int main() {
	Window window("Game", WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	std::vector <vec3> vertexes;
	std::vector <vec3> normals;
	std::vector<vec3> colors;

	//地形生成
	Terrain t;
	t.create();

	TerrainShader tshader("Render Engine/basics/terrain.vert", "Render Engine/basics/terrain.frag");
	tshader.enable();
	tshader.lightpos->load(vec3(0, 100, 50));
	tshader.perspective->load(mat4::perspective(45, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 300));
	tshader.NowlightColor->load(vec4(0.6, 0.7, 0.8,1.0));
	tshader.model->load(mat4::translation(vec3(0, -16,0)));
	tshader.disable();


	//FBO
	
	Fbo * fbo = FboBuilder(480,270).setWindow(&window).creat();

	InvertColor i = InvertColor(480, 270, &window);
	GaussianBlur g = GaussianBlur(480, 270, &window);


	Camera camera(&window);

	int choice = 3;
	
	while (!window.closed()) {
		window.clear();

	
		camera.move();

		//切换后处理
		if (window.isKeyPressed(GLFW_KEY_1)) {
			choice = 1;
		}
		else if (window.isKeyPressed(GLFW_KEY_2)) {
			choice = 2;
		}
		else if (window.isKeyPressed(GLFW_KEY_3)) {
			choice = 3;
		}

//		printf("%d", choice);

		if (choice != 3) {
			fbo->bindFrameBuffer();
		}
		glClearColor(0.6, 0.7, 0.8, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		tshader.enable();
		tshader.view->load(camera.CreateViewMatrix());
		t.render();
		tshader.disable();


		if (choice != 3) {
			fbo->unbindFrameBuffer();

			if (choice == 1) {
				g.carryOutProcessing(fbo->getColourTexture(), 0, true, &window);
			}
			else {
				i.carryOutProcessing(fbo->getColourTexture(), 0, true, &window);
			}
		}
		
		window.update();
	}

	return 0;
}



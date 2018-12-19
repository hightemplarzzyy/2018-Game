#include <iostream>

#include <vector>

#include "windows.h"

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
#include "Render Engine/bloom/bloomEffect.h"
#include "World/dayNightCycle/HorizonColourCycle.h"
#include "World/dayNightCycle/LightColorCycle.h"



#define WINDOW_WIDTH 1920	
#define WINDOW_HEIGHT 1080


int main() {
	Window window("Game", WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	std::vector <vec3> vertexes;
	std::vector <vec3> normals;
	std::vector<vec3> colors;

	HorizonColorCycle h;
	LightColorCycle l;

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
	BloomEffect e = BloomEffect(480, 270, &window);


	Camera camera(&window);

	int choice = 3;

	float dayTime = 30000;//30S

	float preTime = GetTickCount();

	while (!window.closed()) {
		

		float nowTime = (GetTickCount() - preTime) / dayTime;
		if (nowTime > 0.999) {
			preTime = GetTickCount();
			if (nowTime > 1.0) {
				nowTime = 1.0f;
			}
		}

		Color nowSkyColor = h.getColor(nowTime);
		Color nowLightColor = l.getColor(nowTime);

		camera.move();

		//切换后处理
		if (window.isKeyPressed(GLFW_KEY_1)) {//高斯模糊
			choice = 1;
		}
		else if (window.isKeyPressed(GLFW_KEY_2)) {//反相
			choice = 2;
		}
		else if (window.isKeyPressed(GLFW_KEY_3)) {//没有后处理
			choice = 3;
		}
		else if (window.isKeyPressed(GLFW_KEY_4)) {
			choice = 4;
		}

//		printf("%d", choice);

		if (choice != 3) {//需要后处理
			fbo->bindFrameBuffer();
		}
		glClearColor(nowSkyColor.getR(), nowSkyColor.getG(), nowSkyColor.getB(), 1.0);

		window.clear();//不清除会有残影

		tshader.enable();
		tshader.view->load(camera.CreateViewMatrix());
		tshader.NowlightColor->load(vec4(nowLightColor.getR(),nowLightColor.getG(),nowLightColor.getB(),1.0f));
		t.render();
		tshader.disable();


		if (choice != 3) {
			fbo->unbindFrameBuffer();

			if (choice == 1) {
				g.carryOutProcessing(fbo->getColourTexture(), 0, true, &window);
			}
			else if(choice == 2){
				i.carryOutProcessing(fbo->getColourTexture(), 0, true, &window);
			}
			else{
				e.carryOutProcessing(fbo->getColourTexture(), 0, true, &window);
			}
		}
		
		window.update();
	}

	return 0;
}



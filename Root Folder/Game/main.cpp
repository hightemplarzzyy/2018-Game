#include <iostream>

#include <vector>

#include "Render Engine/basics/DIsplayManager.h"
#include "Render Engine/toolbox/maths/maths_func.h"
#include "Render Engine/shaders/dragonshader.h"
#include "Render Engine/buffers/buffer.h"
#include "Render Engine/buffers/indexbuffer.h"
#include "Render Engine/buffers/vertexarray.h"
#include "Render Engine/textures/texture.h"
#include "Source/entity/models.h"
#include "Source/main/camera.h"
#include "World/dayNightCycle/DayNightCycle.h"
#include "Render Engine/lenseFlare/LenseFlare.h"
#include "Render Engine/environment/environment.h"




#define WINDOW_WIDTH 1280	
#define WINDOW_HEIGHT 720

#define TEXTURE_WIDTH 1280
#define TEXTURE_HEIGHT 720

using namespace std;

int main() {

	DisplayManager::cretaDisplay();

	Camera camera(DisplayManager::window);

	DayNightCycle dn;
	dn.addSun();
	dn.update();

	LenseFlare lense = LenseFlare(mat4::perspective(45.0f, DisplayManager::getAspectRatio(), 0.1f, 300.0f),camera.CreateViewMatrix());


	while (!DisplayManager::closedDisplay()) {
		
		//刷新太阳位置
		dn.update();
		EnvironmentVariables::update();
	
		camera.move();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0);
		DisplayManager::clearDisplay();//不清除会有残影

//		lense.doOcclusionTest();
		lense.render(EnvironmentVariables::getLightDirection(), true);
		
		DisplayManager::updateDisplay();
	}

	return 0;
}



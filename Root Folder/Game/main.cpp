#include <iostream>

#include "Render Engine/basics/window.h"
#include "Source/main/camera.h"
#include "Render Engine/demo renderer/demobatchrenderer.h"
#include "Render Engine/water/watermasterrender.h"
#include "Render Engine/basics/DIsplayManager.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720



int main() {
	Window window("Game", WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	DemoBatchRenderer demobatchrenderer;
	

	double x, y;


	Camera camera(&window);

	//LowPolyWater Effect
	//Water water(-2.0, -20, 0, 5);
	//WaterMasterRenderer watermasterrender(&camera, water, &window);

	while (!window.closed()) {
		window.clear();
		window.getMousePosition(x, y);

		demobatchrenderer.getShader()->light_position->load(x * 16.0f / 1280.0f, 9.0f - y * 9.0f / 720.0f);
		demobatchrenderer.render();
		
		//LowPolyWater Effect
		//DisplayManager::updateDelta();
		//camera.move();
		//watermasterrender.render();

		window.update();
	}

	return 0;
}
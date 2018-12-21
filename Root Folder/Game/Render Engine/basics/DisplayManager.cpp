#include "DisplayManager.h"
#include <iostream>

int DisplayManager::SCREEN_WIDTH = 1280;
int DisplayManager::SCREEN_HEIGHT = 720;
const char * DisplayManager::SCREEN_TITLE = "Game";
float DisplayManager::ASPECTRATIO;

int DisplayManager::FPS_CAP = 100;
float DisplayManager::MAX_DELTA = 0.2f;
float DisplayManager::STABLE_DELTA_TIME = 2.0f;

long DisplayManager::LASTFRAMETIME;
float DisplayManager::DELTA;
float DisplayManager::TIME = 0;

Window * DisplayManager::window;

void DisplayManager::cretaDisplay() {
	window = new Window(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	ASPECTRATIO = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	LASTFRAMETIME = getCurrentTime();
	DELTA = 1.0f / FPS_CAP;
}

bool DisplayManager::closedDisplay() {
	return window->closed();
}

void DisplayManager::updateDisplay() {
	updateDelta();
//	printf("Time: %f, Delta: %f\n", TIME, DELTA);
	window->update();
}

void DisplayManager::clearDisplay() {
	window->clear();
}

int DisplayManager::getScreenHeigh() {
	SCREEN_HEIGHT = window->getHeight();
	return SCREEN_HEIGHT;
}

int DisplayManager::getScreenWidth() {
	SCREEN_WIDTH = window->getWidth();
	return SCREEN_WIDTH;
}

bool DisplayManager::isKeyPressed(unsigned int keycode) {
	return window->isKeyPressed(keycode);
}

bool DisplayManager::isMouseButtonPressed(unsigned int button) {
	return window->isMouseButtonPressed(button);
}

void DisplayManager::getMousePosition(double &x, double &y) {
	window->getMousePosition(x, y);
}

long DisplayManager::getCurrentTime() {
	return GetTickCount();
}

void DisplayManager::updateDelta() {
	long currentFramTime = getCurrentTime();
	float nowDelta = (currentFramTime - LASTFRAMETIME) / 1000.0f;
	DELTA = MAX_DELTA < nowDelta ? MAX_DELTA : nowDelta;
	LASTFRAMETIME = currentFramTime;
	TIME += DELTA;
	if (TIME < STABLE_DELTA_TIME) {
		DELTA = 1.0f / FPS_CAP;
	}
}

float DisplayManager::getDelta() {
	return DELTA;
}

float DisplayManager::getTime() {
	return TIME;
}

float DisplayManager::getAspectRatio() {
	return ASPECTRATIO;
}


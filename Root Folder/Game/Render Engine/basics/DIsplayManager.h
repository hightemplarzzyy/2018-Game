#pragma once

#include "window.h"
#include "windows.h"

class DisplayManager {
private:
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	static const char * SCREEN_TITLE;
	static float ASPECTRATIO;

	static int FPS_CAP;
	static float MAX_DELTA;
	static float STABLE_DELTA_TIME;

	static long LASTFRAMETIME;
	static float DELTA;
	static float TIME;


	static long getCurrentTime();
	static void updateDelta();

public:

	static Window * window;

	static void createDisplay();

	static bool closedDisplay();
	static void updateDisplay();
	static void clearDisplay();
	static int getScreenWidth();
	static int getScreenHeigh();

	static float getTime();
	static float getDelta();
	static float getAspectRatio();

	static bool isKeyPressed(unsigned int keycode);
	static bool isMouseButtonPressed(unsigned int button);
	static void getMousePosition(double &x, double &y);


	

};
#include <iostream>

#include "Source/graphics/window.h"
#include "Source/maths/maths.h"

using namespace std;
int main() {
	Window window("Game", 1280, 720);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);


	while (!window.closed()) {
		
		window.clear();
		
#if 1
		glBegin(GL_TRIANGLES);
		glVertex2f(0.0, 0.5);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glEnd();
#endif
		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
		window.update();
	}
	return 0;
}
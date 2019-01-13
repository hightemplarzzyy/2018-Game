#include "CamerManager.h"

Camera * CameraManager::pcamera;

void CameraManager::Init(){
	pcamera = new Camera(vec3(0, 0, 0), vec3(-10, 10, 10));
}

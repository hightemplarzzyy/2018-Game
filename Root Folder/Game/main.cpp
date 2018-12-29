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
#include "Render Engine/postProcessing/GaussianBlur/GaussianBlur.h"
#include "Render Engine/postProcessing/InvertColor/InvertColor.h"
#include "Render Engine/bloom/bloomEffect.h"
#include "World/dayNightCycle/HorizonColourCycle.h"
#include "World/dayNightCycle/LightColorCycle.h"
#include "Render Engine/particles/particleTexture.h"
#include "Render Engine/particles/particleRender.h"
#include "Render Engine/particles/ParticleSystem.h"
#include "Render Engine/particles/particleMaster.h"
#include "Render Engine/particleSpawns/PointSpawn.h"
#include "Render Engine/particleSpawns/CircleSpawn.h"
#include "Resource Management/resourceManagement/ParticleAtlasCache.h"

#define WINDOW_WIDTH 1280	
#define WINDOW_HEIGHT 720

#define TEXTURE_WIDTH 1280
#define TEXTURE_HEIGHT 720

std::vector <GLfloat> buf;
mat4 model = mat4(1.0);
Particle p;
std::vector<Particle> plist;

using namespace std;

int main() {


	DisplayManager::cretaDisplay();

	//加载所有粒子贴图
	ParticleAtlasCache::loadALL();

	HorizonColorCycle h;
	LightColorCycle l;

	//FBO
	Fbo * fbo = FboBuilder(TEXTURE_WIDTH,TEXTURE_HEIGHT).creat();

	//后处理器
	InvertColor i = InvertColor(TEXTURE_WIDTH, TEXTURE_HEIGHT);
	GaussianBlur g = GaussianBlur(TEXTURE_WIDTH, TEXTURE_HEIGHT);
	BloomEffect e = BloomEffect(TEXTURE_WIDTH, TEXTURE_HEIGHT);

	Camera camera(DisplayManager::window);

	int choice = 3;

	float dayTime = 10000;//30S

	float preTime = GetTickCount();


	//例子发射器
	PointSpawn * pSpwan = new PointSpawn();
	CircleSpawn * pCSpwan = new CircleSpawn(vec3(0, 0, 1), 3);
	ParticleSystem tpEmiter = ParticleSystem(ParticleAtlasCache::getAtlas(1), pCSpwan, 2000, 1, 0, 10, 0.2);
	ParticleSystem cpEmiter = ParticleSystem(Color(0.8, 0.0, 0.0), false, pCSpwan, 2000, 0.5, 0, 10, 0.2);
	ParticleSystem acpEmiter = ParticleSystem(Color(0.8, 0.0, 0.0), true, pCSpwan, 2000, 0.5, 0, 10, 0.2);
	tpEmiter.generateParticles(vec3(-0.5, -0.5, 0), 0.2);
	cpEmiter.generateParticles(vec3(0.5, 0.5, 0), 0.5);
	acpEmiter.generateParticles(vec3(-0.5, 0.5, 0), 0.5);


	ParticleMaster::init(camera.CreateViewMatrix());


	while (!DisplayManager::closedDisplay()) {
				 
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
		if (DisplayManager::isKeyPressed(GLFW_KEY_1)) {//高斯模糊
			choice = 1;
		}
		else if (DisplayManager::isKeyPressed(GLFW_KEY_2)) {//反相
			choice = 2;
		}
		else if (DisplayManager::isKeyPressed(GLFW_KEY_3)) {//没有后处理
			choice = 3;
		}
		else if (DisplayManager::isKeyPressed(GLFW_KEY_4)) {
			choice = 4;
		}
			   
		if (choice != 3) {//需要后处理
			fbo->bindFrameBuffer();
		}
		glClearColor(nowSkyColor.getR(), nowSkyColor.getG(), nowSkyColor.getB(), 1.0);

		DisplayManager::clearDisplay();//不清除会有残影


		
		//渲染粒子
		ParticleMaster::renderParticles(camera);
		//更新粒子
		ParticleMaster::update(camera);


		if (choice != 3) {
			fbo->unbindFrameBuffer();

			if (choice == 1) {
				g.carryOutProcessing(fbo->getColourTexture(), 0, true);
			}
			else if(choice == 2){
				i.carryOutProcessing(fbo->getColourTexture(), 0, true);
			}
			else{
				e.carryOutProcessing(fbo->getColourTexture(), 0, true);
			}
		}
		
		DisplayManager::updateDisplay();
	}

	return 0;
}



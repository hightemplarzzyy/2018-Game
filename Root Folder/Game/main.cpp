#include <iostream>

#include <vector>

#include "windows.h"

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

#define WINDOW_WIDTH 1280	
#define WINDOW_HEIGHT 720

#define TEXTURE_WIDTH 1280
#define TEXTURE_HEIGHT 720

std::vector <GLfloat> buf;
mat4 model = mat4(1.0);
Particle p;
std::vector<Particle> plist;


int main() {
	
	
	DisplayManager::cretaDisplay();

	std::vector <vec3> vertexes;
	std::vector <vec3> normals;
	std::vector<vec3> colors;

	HorizonColorCycle h;
	LightColorCycle l;

	//FBO
	Fbo * fbo = FboBuilder(TEXTURE_WIDTH,TEXTURE_HEIGHT).creat();

	InvertColor i = InvertColor(TEXTURE_WIDTH, TEXTURE_HEIGHT);
	GaussianBlur g = GaussianBlur(TEXTURE_WIDTH, TEXTURE_HEIGHT);
	BloomEffect e = BloomEffect(TEXTURE_WIDTH, TEXTURE_HEIGHT);

	Camera camera(DisplayManager::window);

	int choice = 3;

	float dayTime = 30000;//30S

	float preTime = GetTickCount();


	
	VertexArray t_vao;
	GLfloat texPos[8] = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f };
	t_vao.addBuffer(new Buffer(texPos, 8, 2), 0);

	ParticleShader pshader = ParticleShader("Render Engine/particles/particle.vert",
		"Render Engine/particles/particle.frag");
	pshader.enable();
	pshader.projection_matrix->load(camera.CreateViewMatrix());
	pshader.numberOfRaws->load(4);
	pshader.disable();

	//Texture Test
	TextureBuilder tb("cosmic.png");
	Texture t = tb.create();
	ParticleTexture pt = ParticleTexture(t, 4, false);
	std::map<ParticleTexture, std::vector<Particle>> pm;
	ParticleRender pr = ParticleRender(camera.CreateViewMatrix());

	vec3 originalPos = vec3(0, 0, 0);
	float posx, posy, posz;
	float speedx, speedy, speedz;
	for (int i = 0; i < 20; i++) {
		posx = float(rand() % 200) / 1000;
		posy = float(rand() % 200) / 1000;
		posz = -float(i)/20;
		speedx = float(rand() % 400) / 1000;
		speedy = float(rand() % 400) / 1000;
		speedz = 0;
		if (rand() % 2 == 0) {
			speedx = -speedx;
		}
		p = Particle(pt, vec3(posx,posy,posz), vec3(speedx,speedy,speedz), 0.008, 0.16 * 9, 20, 0.2f);
		p.setFade(1.0f, 0.3, 0.7);
		plist.push_back(p);
	}

	pm[pt] = plist;

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
		pr.render(pm, camera);


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



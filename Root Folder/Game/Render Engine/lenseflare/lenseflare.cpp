#include "lenseflare.h"
#include "flaretexture.h"

int LenseFlare::MIDDLE_INDEX = 4;

Texture LenseFlare::circleRings;
Texture LenseFlare::smallGreen;
Texture LenseFlare::rainbowRing;
Texture LenseFlare::smallDot;
Texture LenseFlare::sunStar;
Texture LenseFlare::redDot;
Texture LenseFlare::rainbow2;

Texture LenseFlare::loadTexture(const char * Path) {
	return Texture::newTexture(Path).noFiltering().clampEdges().create();
}

LenseFlare::LenseFlare(mat4 projectionMartrix, mat4 viewMatrix) {
	circleRings		= loadTexture("res/lenseFlare/flare2.png");
	smallGreen		= loadTexture("res/lenseFlare/flare3.png");
	rainbowRing		= loadTexture("res/lenseFlare/flare4.png");
	smallDot		= loadTexture("res/lenseFlare/flare5.png");
	sunStar			= loadTexture("res/lenseFlare/flare6.png");
	redDot			= loadTexture("res/lenseFlare/flare7.png");
	rainbow2		= loadTexture("res/lenseFlare/flare8.png");

	std::vector<FlareTexture> list = {
		FlareTexture(sunStar,1.3f),
		FlareTexture(rainbowRing),
		FlareTexture(circleRings,0.8f),
		FlareTexture(redDot,0.6f),
		FlareTexture(smallGreen,0.6f),
		FlareTexture(smallDot,0.5f),
		FlareTexture(redDot),
		FlareTexture(smallGreen,0.9f),
		FlareTexture(smallDot,0.3f),
		FlareTexture(rainbowRing),
		FlareTexture(rainbow2,1.2f)
	};

	m_FlareManager = new FlareManager(MIDDLE_INDEX, list);
}

LenseFlare::~LenseFlare(){
	delete m_FlareManager;
}

void LenseFlare::render(vec3 lightDirection, bool sunVisible) {
	if (sunVisible) {
		m_FlareManager->render(lightDirection);
	}
}

void LenseFlare::doOcclusionTest() {
	m_FlareManager->doOcclusionTest();
}

void LenseFlare::cleanUp() {
	m_FlareManager->cleanUp();
}
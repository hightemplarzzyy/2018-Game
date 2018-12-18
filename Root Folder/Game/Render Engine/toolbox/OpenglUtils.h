#ifndef _OPENGL_UTILS_H_
#define _OPENGL_UTILS_H_

#include <GL/glew.h>

#include "Color.h"

class OpenglUtils {
private:
	static bool cullingBackFace;
	static bool inWireFrame;
	static bool isAlphaBlending;
	static bool additiveBlending;
	static bool antialiasing;
	static bool scissorTest;
	static int scissorBounds[4];
public:
	static void prepareNewRenderPass(Color skyColour);
	static void prepareNewRenderPass(Color skyColour, float alpha);
	static void prepareNewRenderPassOnlyDepth();
	static void enableScissorTest(int x, int y, int width, int heigh);
	static void disableScissorTest();
	static void prepareNewRenderParse(Color skyColour, float alpha);
	static void antialias(bool enable);
	static void enableAphaBlending();
	static void enableAdditiveBleding();
	static void disabaleBlending();
	static void disabaleDepthTesting();
	static void enableDepthTesting();
	static void cullBackFaces(bool cull);
	static void setWireFrame(bool goWireFrame);
	static void bindTextureToBank(GLuint textureID, int bankID);
	static void bindTextureToBank(GLuint textureID, int bankID, int lodBias);
};

#endif // !_OPENGL_UTILS_H_
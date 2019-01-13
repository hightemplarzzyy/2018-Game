#version 400

in vec2 pass_textureCoords;

out vec4 out_colour;

uniform sampler2D originalTexture;
uniform sampler2D blurredTexture;
uniform sampler2D depthTexture;

uniform float aimDistance;

const float NEAR_FIELD = 0.04;
const float NEAR_TRANS = 0.2;
const float NEAR_END = NEAR_FIELD + NEAR_TRANS;

const float FAR_FIELD = 2.3;
const float FAR_TRANS = 0.35;
const float FAR_START = FAR_FIELD - FAR_TRANS;

//I want to use the glsl smoothstep function, but for some unknown reason it doesn't work on my laptop, but only when exported as a jar. Works fine in Eclipse!
float smoothlyStep(float edge0, float edge1, float x){
  float t = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
  return t * t * (3.0 - 2.0 * t);
}


float getDepthFactor(float depth, float upperLimit){
	return clamp(depth/upperLimit, 0.0, 1.0);
}

float calculateDepth(){
  float near = 0.1;
  float far = 300.0;
  float depth = texture(depthTexture, pass_textureCoords).r;
  return 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
}


void main(void){

  vec3 originalColour = texture(originalTexture, pass_textureCoords).rgb;
  vec3 blurColour = texture(blurredTexture, pass_textureCoords).rgb;

  float depth = calculateDepth();
  float nearVisibility = smoothlyStep(NEAR_FIELD * aimDistance, NEAR_END * aimDistance , depth);
  float farVisibility = 1.0 - smoothlyStep(FAR_START * aimDistance, FAR_FIELD * aimDistance, depth);
  vec3 totalColour = mix(blurColour, originalColour, nearVisibility);
  totalColour = mix(blurColour, totalColour, farVisibility);
  //vec3 totalColour = mix(vec3(1.0,0.0,0.0), vec3(0.0,0.0,1.0), nearVisibility);
  //totalColour = mix(vec3(0.0,1.0,0.0), totalColour, farVisibility);
  out_colour = vec4(totalColour, 1.0);
  //out_colour = vec4(vec3(depth/300),1.0f);
}

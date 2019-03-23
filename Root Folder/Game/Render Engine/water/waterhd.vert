#version 400

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec4 in_indicators;

out float pass_visibility;
out vec4 pass_clipSpace;
out vec4 pass_clipSpace2;
out vec3 pass_diffuse;
out vec3 pass_specular;
out vec3 pass_normal;
out vec3 pass_toCameraVector;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 model;

uniform float worldRadius;
uniform float fadeOutPeriod;

uniform vec3 lightDirection;
uniform vec3 lightColour;
uniform vec3 cameraPosition;

uniform float waveTime;
uniform float waterHeight;
uniform float amplitude;
uniform vec2 mistValues;

uniform vec2 worldCenter;

const float waveLength = 4.0;
const float shineDamper = 20.0;
const float reflectivity = 0.7;
const float fadeDist = 10.0;

const float PI = 3.1415926535897932384626433832795;

float generateOffset(float x, float z, float val1, float val2, float amp){
	float radiansX = ((mod(x+z*x*val1, waveLength)/waveLength) + waveTime) * 2.0 * PI;
	float radiansZ = ((mod(val2 * (z*x +x*z), waveLength)/waveLength) + waveTime * 2.0) * 2.0 * PI;
	return amp * amplitude * 0.5 * (sin(radiansZ) + sin(radiansX));
}

vec3 generateVertexOffset(float x, float z){
	return vec3(generateOffset(x, z, 0.2, 0.1, 1.5), generateOffset(x, z, 0.1, 0.3, 1.0), generateOffset(x, z, 0.15, 0.2, 1.5));
}

float smoothlyStep(float edge0, float edge1, float x){
    float t = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    return t * t * (3.0 - 2.0 * t);
}

vec3 calcNormal(vec3 vertex0, vec3 vertex1, vec3 vertex2){
	vec3 tangent = vertex1 - vertex0;
	vec3 bitangent = vertex2 - vertex0;
	return cross(tangent, bitangent);
}

void main(void){

	vec3 thisVertex = vec3(in_position.x, waterHeight, in_position.y);
	vec3 otherVertex1 = thisVertex + vec3(in_indicators.x, 0.0, in_indicators.y);
	vec3 otherVertex2 = thisVertex + vec3(in_indicators.z, 0.0, in_indicators.w);
	
	pass_clipSpace = projectionMatrix * viewMatrix * model * vec4(thisVertex, 1.0);
	
	thisVertex += generateVertexOffset(thisVertex.x, thisVertex.z);
	otherVertex1 += generateVertexOffset(otherVertex1.x, otherVertex1.z);
	otherVertex2 += generateVertexOffset(otherVertex2.x, otherVertex2.z);

	vec4 worldPosition = model * vec4(thisVertex, 1.0);
	vec4 eyeCoords = viewMatrix * worldPosition;
	pass_clipSpace2 = projectionMatrix * eyeCoords;
	gl_Position = pass_clipSpace2;
	

	vec3 normal = calcNormal(thisVertex, otherVertex1, otherVertex2);
	vec3 surfaceNormal = normalize(normal);	
	vec3 extremeNormal = normalize(vec3(normal.x, normal.y * 0.7, normal.z));	

	vec3 lightVector = -normalize(lightDirection);
	float brightness = max(dot(lightVector, extremeNormal), 0.0);
	pass_diffuse = brightness * lightColour;
	pass_normal = surfaceNormal;
	
	vec3 viewVector = normalize(cameraPosition - worldPosition.xyz);
	pass_toCameraVector = viewVector;
	vec3 reflectedLightDirection = reflect(-lightVector, extremeNormal);
	float specularFactor = dot(reflectedLightDirection , viewVector);
	specularFactor = max(specularFactor,0.0);
	specularFactor = pow(specularFactor, shineDamper);
	pass_specular = specularFactor * lightColour * reflectivity;
	

	vec2 worldCoords = worldPosition.xz - vec2(worldRadius);
	worldCoords = abs(worldCoords);
	vec2 fadeVals =1.0 - vec2(smoothlyStep(worldRadius - 6.0, worldRadius, worldCoords.x), smoothlyStep(worldRadius - 6.0, worldRadius, worldCoords.y));
	pass_visibility = 1.0 - smoothlyStep(mistValues.x, mistValues.y, -eyeCoords.z)*0.5;
	
}
#version 400

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec4 in_indicators;

out vec3 pass_colour;
out float pass_visibility;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 model;

uniform float waterHeight;
uniform float waveTime;
uniform float amplitude;
uniform float squareSize;
uniform vec2 mistValues;
uniform vec3 lightDirection;
uniform vec3 lightColour;
uniform vec3 cameraPosition;
uniform float worldRadius;
uniform float fadeOutPeriod;
uniform vec2 worldCenter;

const float waveLength = 4.0;
const float shineDamper = 20.0;
const float reflectivity = 0.5;


const vec3 waterColour = vec3(0.568, 0.844, 0.756);

const float PI = 3.1415926535897932384626433832795;

float generateHeightOffset(float x, float z)
{
	float radiansX = ((mod(x+z*x*0.1, waveLength)/waveLength) + waveTime) * 2.0 * PI;
	float radiansZ = ((mod(0.3 * (z*x +x*z), waveLength)/waveLength) + waveTime * 2.0) * 2.0 * PI;
	return amplitude * 0.5 * (sin(radiansZ) + sin(radiansX));
}

float smoothlyStep(float edge0, float edge1, float x)
{
    float t = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    return t * t * (3.0 - 2.0 * t);
}

vec3 calcNormal(vec3 vertex0, vec3 vertex1, vec3 vertex2)
{
	vec3 tangent = vertex1 - vertex0;
	vec3 bitangent = vertex2 - vertex0;
	return normalize(cross(tangent, bitangent));
}

void main(void)
{
	vec3 thisVertex = vec3(in_position.x, waterHeight, in_position.y);
	vec3 otherVertex1 = thisVertex + vec3(in_indicators.x, 0.0, in_indicators.y);
	vec3 otherVertex2 = thisVertex + vec3(in_indicators.z, 0.0, in_indicators.w);
	
	thisVertex.y += generateHeightOffset(thisVertex.x, thisVertex.z);
	otherVertex1.y += generateHeightOffset(otherVertex1.x, otherVertex1.z);
	otherVertex2.y += generateHeightOffset(otherVertex2.x, otherVertex2.z);

	vec4 worldPosition = model *  vec4(thisVertex, 1.0);
	vec4 eyeCoords = viewMatrix * worldPosition;
	gl_Position = projectionMatrix * eyeCoords;

	vec3 surfaceNormal = calcNormal(thisVertex, otherVertex1, otherVertex2);
	vec3 lightVector = -normalize(lightDirection);
	float brightness = max(dot(lightVector, surfaceNormal), 0.0);
	vec3 diffuse = brightness * lightColour;

	vec3 viewVector = normalize(cameraPosition - worldPosition.xyz);
	vec3 reflectedLightDirection = reflect(-lightVector, surfaceNormal);
	float specularFactor = dot(reflectedLightDirection , viewVector);
	specularFactor = max(specularFactor,0.0);
	specularFactor = pow(specularFactor, shineDamper);
	vec3 specular = specularFactor * lightColour * reflectivity;
	
	pass_colour = diffuse * waterColour + specular;
	pass_visibility = 1.0 - smoothlyStep(mistValues.x, mistValues.y, -eyeCoords.z)*0.5;
}
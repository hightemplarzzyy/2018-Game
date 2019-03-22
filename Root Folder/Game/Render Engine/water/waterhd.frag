#version 400

in vec3 pass_diffuse;
in vec3 pass_specular;
in vec3 pass_normal;
in vec3 pass_toCameraVector;
in float pass_visibility;
in vec4 pass_clipSpace;
in vec4 pass_clipSpace2;

uniform sampler2D reflectionTexture;
uniform sampler2D depthTexture;

uniform vec2 frustumNearFar;
uniform vec3 skyColour;
uniform vec3 mistColour;
out vec4 out_colour;

const float edgeSoftness = 0.2;
const float waterClearness = 15.0;
const vec3 waterColour = vec3(0.568, 0.844, 0.756);//0.6, 0.74, 0.76
const float reflectiveness = 0.8;
const float overallBlueness = 0.65;
const float minVisible = 0.3;

float getDepthFactor(float depth, float upperLimit){
	return clamp(depth/upperLimit, 0.0, 1.0);
}

float calculateFresnel(){
	vec3 viewVector = normalize(pass_toCameraVector);
	vec3 normal = normalize(vec3(pass_normal.x, pass_normal.y*0.8, pass_normal.z));
	float refractiveFactor = dot(viewVector, normal);
	refractiveFactor = pow(refractiveFactor, reflectiveness);
	return clamp(refractiveFactor, 0.0, 1.0);
}

float calculateWaterDepth(vec2 refractionTextureCoords){
	float near = frustumNearFar.x;
	float far = frustumNearFar.y;
	
	float depth = texture(depthTexture, refractionTextureCoords).r;
	float floorDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
	
	depth = gl_FragCoord.z;
	float waterDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));	
	return floorDistance - waterDistance;
}

vec2 getRefractionTexCoords(vec2 normalizedDeviceCoords){
	vec2 refractionTextureCoords = normalizedDeviceCoords;
	refractionTextureCoords = clamp(refractionTextureCoords, 0.001, 0.999);
	return refractionTextureCoords;
}

vec2 getReflectionTexCoords(vec2 normalizedDeviceCoords){
	vec2 reflectionTextureCoords = vec2(normalizedDeviceCoords.x, -normalizedDeviceCoords.y);
	reflectionTextureCoords.x = clamp(reflectionTextureCoords.x, 0.001, 0.999);
	reflectionTextureCoords.y = clamp(reflectionTextureCoords.y, -0.999, -0.001);
	return reflectionTextureCoords;
}

void main(void){

	vec2 normalizedDeviceCoords = (pass_clipSpace.xy/pass_clipSpace.w)/2.0 + 0.5;
	vec2 normalizedDeviceCoords2 = (pass_clipSpace2.xy/pass_clipSpace2.w)/2.0 + 0.5;
	vec2 refractionTextureCoords = getRefractionTexCoords(normalizedDeviceCoords);
	vec2 reflectionTextureCoords = getReflectionTexCoords(normalizedDeviceCoords);
	
	float waterDepth = calculateWaterDepth(getRefractionTexCoords(normalizedDeviceCoords2));	
	float refractiveFactor = calculateFresnel();
	
	vec3 reflectionColour = texture(reflectionTexture, reflectionTextureCoords).rgb;
	vec3 finalColour = mix(reflectionColour, waterColour, overallBlueness);
	finalColour = pass_diffuse * finalColour + pass_specular;
	
	out_colour = vec4(mix(mistColour, finalColour, pass_visibility), 1.0);
	out_colour.a = min(minVisible + (1 - refractiveFactor) * (1.0 - minVisible), getDepthFactor(waterDepth, edgeSoftness));
	
}
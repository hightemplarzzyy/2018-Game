#version 440 core

out vec4 color;

in vec3 Normal;
in vec3 FragPos;
in vec3 NowColor;
in vec3 NewLightPos;

uniform vec4 NowlightColor;
uniform vec3 viewPos;

float specularStrength = 0.1f;

void main(){

	vec3 lightColor = vec3(NowlightColor);

	//Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(NewLightPos - FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diff * lightColor;

//	vec3 viewDir = normalize(viewPos - FragPos);
//	vec3 reflectDir = reflect(-lightDir, norm);
//	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 2);
//	vec3 specular = specularStrength * spec * lightColor;

//	vec3 result = (diffuse  + specular ) * vec3(NowColor);

	vec3 result = diffuse * vec3(NowColor);

	color = vec4(result,1.0f);
}
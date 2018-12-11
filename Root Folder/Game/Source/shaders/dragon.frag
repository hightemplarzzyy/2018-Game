#version 430 core

out vec4 color;

uniform vec3 light_position;

in DATA{
	vec3 surfaceNormal;
	vec3 WorldPosition;
	vec4 color1;
}fs_in;

void main(){

	vec3 norm;
	vec3 toLight;
	float diffuse;

	norm = normalize(fs_in.surfaceNormal);
	toLight = normalize(light_position - fs_in.WorldPosition);

	diffuse = max(dot(norm, toLight), 0.0);

	color = fs_in.color1 * diffuse;
}
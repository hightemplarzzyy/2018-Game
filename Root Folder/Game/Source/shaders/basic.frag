#version 400 core

out vec4 color;

uniform vec2 light_position;
float coe[3] = float[](2,3,4);

in DATA{
	vec4 position;
	vec4 color;

}fs_in;

in vec4 pos;

void main(){

	float intensity = 1.0 / length(fs_in.position.xy - light_position);
	color = fs_in.color * intensity;

}
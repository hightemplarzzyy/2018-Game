#version 460 core

out vec4 color;

//uniform vec4 color1;
uniform vec2 light_position;

in DATA{
	vec4 position;
	vec4 color;

}fs_in;

in vec4 pos;

void main(){

	float intensity = 1.0 / length(fs_in.position.xy - light_position);
	color = fs_in.color * intensity;

	//float intensity = 1.0 / length(pos.xy - light_position);
	//color = color1 * intensity;
}
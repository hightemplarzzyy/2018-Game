#version 400 core

uniform vec3 light_position;
uniform vec3 light_color;

out vec4 color;

in DATA {
	flat vec4 color;
}fs_in;

void main() {
	color = fs_in.color;
}
#version 400 core

out vec4 color;

uniform vec3 light_position;
uniform sampler2D diff_map;

in DATA{
	vec3 surfaceNormal;
	vec3 WorldPosition;
	vec2 tex;
	vec4 color1;
}fs_in;

void main(){

	vec3 norm;
	vec3 toLight;
	float nol;

	vec4 diff = texture(diff_map, fs_in.tex);
	norm = normalize(fs_in.surfaceNormal);
	toLight = normalize(light_position - fs_in.WorldPosition);

	nol = max(dot(norm, toLight), 0.0);

	color = nol * diff;

	color = color / (color + vec4(1.0));
    color = pow(color, vec4(1.0/2.2));
}
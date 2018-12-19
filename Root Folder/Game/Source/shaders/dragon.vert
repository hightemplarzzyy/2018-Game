#version 400 core

layout (location=0) in vec3 position;
layout (location=1) in vec3 normals;
layout (location=2) in vec2 texcoords;
layout (location=3) in vec4 colors;

uniform mat4 projection_matrix = mat4(1.0);
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 model_matrix = mat4(1.0);

out DATA{
	vec3 surfaceNormal;
	vec3 WorldPosition;
	vec2 tex;
	vec4 color1;
}vs_out;

void main(){
	vs_out.WorldPosition = (model_matrix * vec4(position,1.0)).xyz;
	gl_Position = projection_matrix * view_matrix * vec4(vs_out.WorldPosition,1.0);
	vs_out.surfaceNormal =  normals;
	vs_out.tex = texcoords;
	vs_out.color1 = colors;
}
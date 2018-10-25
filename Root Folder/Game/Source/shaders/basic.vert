#version 460 core

layout (location=0) in vec4 position;
layout (location=1) in vec4 color;

uniform mat4 projection_matrix = mat4(1.0);
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 model_matrix = mat4(1.0);

out DATA{
	vec4 position;
	vec4 color;

}vs_out;

//out vec4 pos;

void main(){
	gl_Position =  projection_matrix * model_matrix * position;
	vs_out.position =  model_matrix * position;
	vs_out.color = color;

	//gl_Position = projection_matrix * model_matrix * position;
	//pos = model_matrix * position;

}
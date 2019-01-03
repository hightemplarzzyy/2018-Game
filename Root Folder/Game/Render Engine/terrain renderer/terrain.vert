#version 400 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

uniform mat4 projection_matrix = mat4(1.0);
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 model_matrix = mat4(1.0);

out DATA {
	flat vec4 color;
}vs_out;

void main() {
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(aPosition, 1.0);
	vs_out.color = vec4(aColor, 1.0f);
}
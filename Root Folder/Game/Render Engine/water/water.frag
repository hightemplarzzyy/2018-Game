#version 400

out vec4 out_colour;

in vec3 pass_colour;
in float pass_visibility;

uniform vec3 mistColour;

const float alpha = 0.55;

void main(void)
{
	out_colour = vec4(mix(mistColour, pass_colour, pass_visibility), alpha);
}
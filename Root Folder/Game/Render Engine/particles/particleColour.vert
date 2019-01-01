#version 400

layout (location = 0) in vec2 position;
layout (location = 1) in mat4 model_matrix;
layout (location = 5) in vec4 colour;
layout (location = 6) in float alpha;

out vec2 textureCoords;
out vec4 pass_colour;

uniform mat4 projection_matrix;
uniform vec3 light_colour;

void main(){
  textureCoords = position + vec2(0.5,0.5);
  textureCoords.y = 1.0f - textureCoords.y;
  
  pass_colour = vec4(colour.rgb * light_colour,alpha);

  gl_Position = projection_matrix * model_matrix * vec4(position,0.0,1.0);
}

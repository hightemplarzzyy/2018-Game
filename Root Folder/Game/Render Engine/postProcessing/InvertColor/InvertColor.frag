#version 440

in vec2 TexCoords;
out vec4 color;

uniform sampler2D screenTexture;

void main(){
  color = texture(screenTexture, TexCoords);
  float average = (color.r + color.g + color.b) / 3.0;
  color = vec4(average, average, average, 1.0);
}

#version 400

in vec2 pass_textureCoords;

out vec4 out_color;

uniform sampler2D originalTexture;
uniform sampler2D bloomTexture;

uniform float bloomBrightness = 0.7;

void main(){
  vec4 color = texture(originalTexture,pass_textureCoords);
  vec4 bloomColor = texture(bloomTexture,pass_textureCoords);
  out_color = vec4(color.rgb + bloomColor.rgb * bloomBrightness,1.0);
  out_color.rgb = (out_color.rgb - 0.46) * (0.15 + 1.0) + 0.54;
}

#version 400

in vec2 pass_textureCoords;

out vec4 out_color;

uniform sampler2D originalTexture;

const float threshold = 0.85;
const float bloomBrightness = 2.0;

void main(){
  vec4 color = texture(originalTexture,pass_textureCoords);
  float brightness = length(color.rgb);//通过获取长度来判定亮度值
  out_color = vec4(0.0);
  if(brightness > threshold){
    brightness = (brightness - threshold);
    out_color.rbg = color.rgb * clamp(brightness * bloomBrightness, 0.0, 1.0);//三个值里面选中间那个值
  }

}

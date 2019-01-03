#version 400

layout (location = 0) in vec2 in_position;

out vec2 pass_textureCoords;
out vec2 pass_blurTextureCoords;

uniform vec4 transform;
uniform int flipTexture;//是否需要翻转y轴

void main(){
  pass_textureCoords = in_position;

  if(bool(flipTexture)){
    pass_textureCoords.y = 1 - pass_textureCoords.y;
  }

  //zw是缩放的比例，xy是位置
  vec2 screenPosition = in_position * transform.zw + transform.xy;

  pass_blurTextureCoords = vec2(screenPosition.x, 1.0-screenPosition.y);
  screenPosition.x = screenPosition.x * 2.0 -1.0;
  screenPosition.y = screenPosition.y * -2.0 + 1.0;

  gl_Position = vec4(screenPosition,0.9999,1.0);
}

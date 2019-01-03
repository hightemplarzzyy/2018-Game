#version 400

layout (location = 0) in vec2 in_position;

out vec2 pass_textureCoords;

void main(){
  //将OpenGl坐标变换为纹理坐标
  pass_textureCoords = in_position * 0.5 + 0.5;

  gl_Position = vec4(in_position,0.0,1.0);
}

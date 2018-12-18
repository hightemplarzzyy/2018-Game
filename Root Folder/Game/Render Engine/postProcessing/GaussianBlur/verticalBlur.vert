#version 400

layout (location = 0) in vec2 in_postion;

out vec2 pass_textureCoords;
out vec2 pass_blurTextureCoords[14];

uniform float height;

void main(){

  //OPENGL坐标转图片坐标
  pass_textureCoords = in_postion * 0.5 + 0.5;

  gl_Position = vec4(in_postion,0.0,1.0);

  //计算点间隔
  float part = 1.0 / height;
  //水平方向取14个点
  pass_blurTextureCoords[0] = pass_textureCoords + vec2(0.0, -part * 7.0);
  pass_blurTextureCoords[1] = pass_textureCoords + vec2(0.0, -part * 6.0);
  pass_blurTextureCoords[2] = pass_textureCoords + vec2(0.0, -part * 5.0);
  pass_blurTextureCoords[3] = pass_textureCoords + vec2(0.0, -part * 4.0);
  pass_blurTextureCoords[4] = pass_textureCoords + vec2(0.0, -part * 3.0);
  pass_blurTextureCoords[5] = pass_textureCoords + vec2(0.0, -part * 2.0);
  pass_blurTextureCoords[6] = pass_textureCoords + vec2(0.0, -part);
  pass_blurTextureCoords[7] = pass_textureCoords + vec2(0.0,  part);
  pass_blurTextureCoords[8] = pass_textureCoords + vec2(0.0,  part * 2.0);
  pass_blurTextureCoords[9] = pass_textureCoords + vec2(0.0,  part * 3.0);
  pass_blurTextureCoords[10] = pass_textureCoords + vec2(0.0,  part * 4.0);
  pass_blurTextureCoords[11] = pass_textureCoords + vec2(0.0,  part * 5.0);
  pass_blurTextureCoords[12] = pass_textureCoords + vec2(0.0,  part * 6.0);
  pass_blurTextureCoords[13] = pass_textureCoords + vec2(0.0,  part * 7.0);

}

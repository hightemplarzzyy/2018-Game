#version 400

layout (location = 0) in vec2 in_position;
//layout (location = 1) in vec2 tex_position;

out vec2 TexCoords;

void main(){
  //将OpenGl坐标变换为纹理坐标
  //TexCoords = tex_position;
  TexCoords = in_position + 0.5;
  TexCoords.y = 1-TexCoords.y;
  gl_Position = vec4(in_position,0.0,1.0);
}
#version 400

layout (location = 0) in vec2 positon;
layout (location = 1) in mat4 model_matrix;
//1,2,3,4 存储整个矩阵
layout (location = 5) in vec4 texOffets;
layout (location = 6) in float blendFactor;

out vec2 textureCoords1;
out vec2 textureCoords2;
out float blend;
out float worldHeight;

uniform mat4 projection_matrix;
uniform float numberOfRows;

void main(){
    //转换坐标系
    //由图片坐标系转换为OpenGL坐标系
    vec2 textureCoords = positon + vec2(0.5,0.5);
    textureCoords.y = 1.0 - textureCoords.y;

    textureCoords /= numberOfRows;
    textureCoords1 = textureCoords + texOffets.xy;
    textureCoords2 = textureCoords + texOffets.zw;
    blend = blendFactor;

    gl_Position = projection_matrix * model_matrix * vec4(positon,0.0,1.0);
}
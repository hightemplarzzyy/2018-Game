#version 400

in vec2 pass_textureCoords;
in vec2 pass_blurTextureCoords[14];

out vec4 out_colour;

uniform sampler2D originalTexture;

void main(){
  out_colour = vec4(0.0);

  out_colour += texture(originalTexture, pass_blurTextureCoords[0])*0.0044299121055113265;
  out_colour += texture(originalTexture, pass_blurTextureCoords[1])*0.00895781211794;
  out_colour += texture(originalTexture, pass_blurTextureCoords[2])*0.0215963866053;
  out_colour += texture(originalTexture, pass_blurTextureCoords[3])*0.0443683338718;
  out_colour += texture(originalTexture, pass_blurTextureCoords[4])*0.0776744219933;
  out_colour += texture(originalTexture, pass_blurTextureCoords[5])*0.115876621105;
  out_colour += texture(originalTexture, pass_blurTextureCoords[6])*0.147308056121;
  out_colour += texture(originalTexture, pass_textureCoords) * 0.159576912161;
  out_colour += texture(originalTexture, pass_blurTextureCoords[7])*0.147308056121;
  out_colour += texture(originalTexture, pass_blurTextureCoords[8])*0.115876621105;
  out_colour += texture(originalTexture, pass_blurTextureCoords[9])*0.0776744219933;
  out_colour += texture(originalTexture, pass_blurTextureCoords[10])*0.0443683338718;
  out_colour += texture(originalTexture, pass_blurTextureCoords[11])*0.0215963866053;
  out_colour += texture(originalTexture, pass_blurTextureCoords[12])*0.00895781211794;
  out_colour += texture(originalTexture, pass_blurTextureCoords[13])*0.0044299121055113265;
}

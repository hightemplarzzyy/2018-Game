#version 400

in vec2 pass_textureCoords;
in vec2 pass_blurTextureCoords;

out vec4 out_color;
uniform sampler2D guiTexture;
uniform sampler2D blurTexture;
uniform float alpha;
uniform vec3 overrideColor;
uniform int usesBlur;
uniform int useOverrideColor;

void main(){
  out_color = texture(guiTexture,pass_textureCoords);
  float brightness = (out_color.r + out_color.g + out_color.b) / 3.0f;

  if(bool(useOverrideColor)){
    out_color.rgb = overrideColor * brightness;
  }

  if(bool(usesBlur)){
    vec4 blurColor = texture(blurTexture, pass_blurTextureCoords);
    out_color.rgb = mix(blurColor.rgb, out_color.rgb, alpha);
  }
  else{
    out_color.a *= alpha;
  }

}

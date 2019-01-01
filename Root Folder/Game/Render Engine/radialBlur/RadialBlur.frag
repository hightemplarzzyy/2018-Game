#version 400

in vec2 pass_textureCoords;

out vec4 out_colour;

uniform sampler2D originalTexture;

const float exposure = 0.7;
const float decay = 0.98; //衰减度
const float density =1.0; //密度
const float weight = 3.0;

uniform vec2 lightPositionOnScreen;

const int NUM_SAMPLES = 100;

void main(){
  vec2 textureCoords = pass_textureCoords;
  vec2 toLight = lightPositionOnScreen - textureCoords;
  toLight *= (1.0/NUM_SAMPLES) * density; //采样

  float illuminationDecay = 1.0;
  out_colour = vec4(0.0,0.0,0.0,1.0);

  for(int i = 0; i < NUM_SAMPLES ;i++){
    vec4 sample = texture(originalTexture,textureCoords);
    out_colour += (sample * illuminationDecay * weight) / NUM_SAMPLES;
    illuminationDecay *= decay;//离的越远影响越小
    textureCoords += toLight;//延径向移动
  }

  out_colour *= exposure;

}

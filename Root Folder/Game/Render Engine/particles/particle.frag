#version 440

out vec4 out_colour;

in vec2 textureCoords1;
in vec2 textureCoords2;
in float blend;

uniform sampler2D particleTexture;
uniform vec3 light_colour;

void main(){
    vec4 colour1 = texture(particleTexture,textureCoords1);
    vec4 colour2 = texture(particleTexture,textureCoords2);
    out_colour = mix(colour1,colour2,blend);
    out_colour.rgb *= light_colour;
}

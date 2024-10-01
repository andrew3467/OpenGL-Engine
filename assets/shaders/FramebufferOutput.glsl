#type vertex
#version 460


layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;


out VS_OUT{
    vec2 TexCoord;
} vs_out;

uniform mat4 uViewProj;

void main() {
    vs_out.TexCoord = aTexCoord;
    gl_Position =  uViewProj * vec4(aPosition, 1.0);
}



#type fragment
#version 460

layout (location = 0) out vec4 FragColor;


in VS_OUT{
    vec2 TexCoord;
} fs_in;


layout (binding = 0) uniform sampler2D uAlbedoMap;


void main() {
    FragColor = texture(uAlbedoMap, fs_in.TexCoord);
}
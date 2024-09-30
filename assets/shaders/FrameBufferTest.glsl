#type vertex
#version 460


layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;


out VS_OUT{
    vec3 FragPos;
    vec2 TexCoord;
    vec3 Normal;
} vs_out;

uniform mat4 uViewProj;
uniform mat4 uModel;

void main() {
    vs_out.TexCoord = aTexCoord;
    vs_out.Normal = aNormal;

    vs_out.FragPos = vec3(uModel * vec4(aPosition, 1));

    gl_Position = uViewProj * uModel * vec4(aPosition, 1.0);
}



#type fragment
#version 460

layout (location = 0) out vec4 FragColor;

in VS_OUT{
    vec3 FragPos;
    vec2 TexCoord;
    vec3 Normal;
} fs_in;

uniform vec3 uColor;


layout (binding = 0) uniform sampler2D uAlbedoMap;


void main() {
    FragColor = vec4(uColor, 1.0) * texture(uAlbedoMap, fs_in.TexCoord);
}
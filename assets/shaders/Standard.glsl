#type vertex
#version 460


layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;

out vec3 vPosition;
out vec2 vTexCoord;

uniform mat4 uViewProj;
uniform mat4 uModel;

void main() {
    vPosition = aPosition;
    vTexCoord = aTexCoord;


    gl_Position = uViewProj * uModel * vec4(aPosition, 1.0);
}



#type fragment
#version 460

layout (location = 0) out vec4 FragColor;

in vec2 vTexCoord;


uniform vec3 uColor;


uniform sampler2D uAlbedoMap;


in vec3 vPosition;


void main() {
    FragColor = texture(uAlbedoMap, vTexCoord);
}
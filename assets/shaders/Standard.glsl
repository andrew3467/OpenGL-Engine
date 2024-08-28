#type vertex
#version 460


layout (location = 0) in vec3 aPosition;

out vec3 vPosition;

uniform mat4 uViewProj;
uniform mat4 uModel;

void main() {
    vPosition = aPosition;


    gl_Position = uViewProj * uModel * vec4(aPosition, 1.0);
}



#type fragment
#version 460

layout (location = 0) out vec4 FragColor;


uniform vec3 uColor;


in vec3 vPosition;


void main() {
    FragColor = vec4(uColor, 1.0);
}
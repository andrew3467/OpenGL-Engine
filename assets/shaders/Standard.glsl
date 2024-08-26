#type vertex
#version 460


layout (location = 0) in vec3 aPosition;


out vec3 vPosition;

void main() {
    vPosition = aPosition;


    gl_Position = vec4(aPosition, 1.0);
}



#type fragment
#version 460

layout (location = 0) out vec4 FragColor;


uniform vec3 uColor;


in vec3 vPosition;


void main() {
    FragColor = vec4(uColor, 1.0);
}
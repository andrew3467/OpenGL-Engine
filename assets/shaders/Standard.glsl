#type vertex
#version 460


layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 vNormal;
out vec3 vFragPos;
out vec2 vTexCoord;

uniform mat4 uViewProj;
uniform mat4 uModel;

void main() {
    vNormal = aNormal;
    vTexCoord = aTexCoord;

    vFragPos = vec3(uModel * vec4(aPosition, 1));

    gl_Position = uViewProj * uModel * vec4(aPosition, 1.0);
}



#type fragment
#version 460

struct PointLight {
    vec3 Color;
    vec3 Position;
};

const int MAX_POINT_LIGHTS = 32;



layout (location = 0) out vec4 FragColor;

in vec3 vFragPos;
in vec2 vTexCoord;
in vec3 vNormal;


uniform int uNumLights;
uniform PointLight uPointLights[MAX_POINT_LIGHTS];

uniform vec3 uViewPos;


uniform vec3 uColor;


layout (binding = 0) uniform sampler2D uAlbedoMap;       //Slot 0
layout (binding = 1) uniform sampler2D uDiffuseMap;      //Slot 1
layout (binding = 2) uniform sampler2D uNormalMap;       //Slot 2

void main() {
    FragColor = texture(uAlbedoMap, vTexCoord) * vec4(uColor, 1);
}
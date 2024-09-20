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
    vec3 Position;
    vec3 Color;
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

vec3 calcDirLight() {
    return vec3(0);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewPos) {
    vec3 lightDir = normalize(light.Position - vFragPos);

    vec3 viewDir = normalize(viewPos - vFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    const float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * light.Color;

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.Color;

    const float specularStrength = 0.5f;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * light.Color;

    return ambient + diffuse + specular;
}

void main() {
    vec3 normal = normalize(vNormal);

    vec3 result = calcDirLight();
    for(int i = 0; i < uNumLights; i++) {
        result += calcPointLight(uPointLights[i], normal, uViewPos);
    }

    FragColor = texture(uAlbedoMap, vTexCoord) * vec4(result, 1);
}
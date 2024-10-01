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
uniform mat4 uModels[256];

uniform bool uInstanced;

void main() {
    vs_out.Normal = aNormal;
    vs_out.TexCoord = aTexCoord;

    if (uInstanced) {
        gl_Position = uViewProj * uModels[gl_InstanceID] * vec4(aPosition, 1.0);
        vs_out.FragPos = vec3(uModels[gl_InstanceID] * vec4(aPosition, 1));
    } else {
        gl_Position = uViewProj * uModels[0] * vec4(aPosition, 1.0);
        vs_out.FragPos = vec3(uModels[0] * vec4(aPosition, 1));
    }

    gl_Position = vec4(aPosition, 1);
}



#type fragment
#version 460

struct PointLight {
    vec3 Color;
    vec3 Position;
};

const int MAX_POINT_LIGHTS = 32;



layout (location = 0) out vec4 FragColor;

in VS_OUT{
    vec3 FragPos;
    vec2 TexCoord;
    vec3 Normal;
} fs_in;


uniform int uNumLights;
uniform PointLight uPointLights[MAX_POINT_LIGHTS];

uniform vec3 uViewPos;


uniform vec3 uColor;


layout (binding = 0) uniform sampler2D uAlbedoMap;       //Slot 0
layout (binding = 1) uniform sampler2D uDiffuseMap;      //Slot 1
layout (binding = 2) uniform sampler2D uNormalMap;       //Slot 2

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(light.Position - fs_in.FragPos);

    const float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light.Color;


    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.Color;


    const int shininess = 32;
    const float specularStrenth = 0.5;
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0), shininess);
    vec3 specular = specularStrenth * spec * light.Color;

    return ambient + diffuse + specular;
}

void main() {
    vec3 normal = normalize(fs_in.Normal);
    vec3 viewDir = normalize(uViewPos - fs_in.FragPos);

    vec3 outColor = texture(uAlbedoMap, fs_in.TexCoord).rgb;

    vec3 lighting = vec3(0);
    for(int i = 0; i < uNumLights; i++) {
        lighting += calcPointLight(uPointLights[i], normal, fs_in.FragPos);
    }

    outColor *= lighting;

    FragColor = vec4(outColor, 1);
}
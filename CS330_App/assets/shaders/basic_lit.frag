#version 330 core

struct DirLight {
    vec3 Direction;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

struct PointLight {
    vec3 Position;

    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    float Constant;
    float Linear;
    float Quadratic;
};

out vec4 FragColor;

in vec4 vertexColor;
in vec3 fragNormal;
in vec3 fragPosition;

in vec2 texCoord;

uniform sampler2D tex0; // GL_TEXTURE0
uniform sampler2D tex1; // GL_TEXTURE1
uniform sampler2D tex2; // GL_TEXTURE2

uniform vec3 eyePos;

#define MAX_POINT_LIGHTS 4
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform DirLight dirLight;

vec3 CalcDirLight(vec3 normal, vec3 viewDir) {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * dirLight.Ambient;

    // diffuse
    vec3 lightDir = dirLight.Direction;
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * dirLight.Diffuse;

    // specular
    float specularStrength = 1.f;
    float shininess = 256;

    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0)), shininess;
    vec3 specular = specularStrength * spec * dirLight.Specular;

    vec3 dirLightColor = (diffuse + specular + ambient);

    return dirLightColor;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir) {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light.Ambient;

    // diffuse
    vec3 lightDir = normalize(light.Position - fragPosition);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.Diffuse;

    // specular
    float specularStrength = 1.f;
    float shininess = 256;

    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0)), shininess;
    vec3 specular = specularStrength * spec * light.Specular;

    float distance = length(light.Position - fragPosition);
    float attenuation = 1.0 / (light.Constant + (light.Linear * distance) + light.Quadratic * (distance * distance));

    return (diffuse + specular + ambient) * attenuation;
}

void main() {
    vec3 objectColor = vec3(vertexColor * texture(tex0, texCoord));

    vec3 norm = normalize(fragNormal);
    vec3 viewDir = normalize(eyePos - fragPosition);

    vec3 result = CalcDirLight(norm, viewDir);

    for (int i = 0; i < MAX_POINT_LIGHTS; i++) {
        result += CalcPointLight(pointLights[i], norm, viewDir);
    }

    vec3 finalColor = result * objectColor;
    FragColor = vec4(finalColor, 1.0);
}
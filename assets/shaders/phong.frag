#version 330 core
in vec3 FragPos;
in vec3 VertexColor;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D uTexture;
uniform vec3 uViewPos;
uniform float uShininess;

uniform bool uPointLightEnabled;
uniform bool uDirLightEnabled;

// Point light
uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform float uAmbientStrength;
uniform float uSpecularStrength;
uniform float uLightConstant;
uniform float uLightLinear;
uniform float uLightQuadratic;

// Directional light
uniform vec3 uDirLightDirection;
uniform vec3 uDirLightColor;
uniform float uDirAmbientStrength;
uniform float uDirSpecularStrength;

vec3 CalcPointLight(vec3 norm, vec3 viewDir, vec3 texColor) {
    vec3 lightDir = normalize(uLightPos - FragPos);
    float distance = length(uLightPos - FragPos);
    float attenuation = 1.0 / (uLightConstant + uLightLinear * distance +
    uLightQuadratic * (distance * distance));

    vec3 ambient = uAmbientStrength * uLightColor;
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * uLightColor;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), uShininess);
    vec3 specular = uSpecularStrength * spec * uLightColor;

    return (ambient + diffuse) * attenuation * texColor + specular * attenuation;
}

vec3 CalcDirLight(vec3 norm, vec3 viewDir, vec3 texColor) {
    vec3 lightDir = normalize(-uDirLightDirection); // pointing FROM the fragment TOWARD the light

    vec3 ambient = uDirAmbientStrength * uDirLightColor;
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * uDirLightColor;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), uShininess);
    vec3 specular = uDirSpecularStrength * spec * uDirLightColor;

    // No attenuation - directional lights don't fall off with distance
    return (ambient + diffuse) * texColor + specular;
}

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(uViewPos - FragPos);
    vec3 texColor = texture(uTexture, TexCoords).rgb;

    vec3 result = vec3(0.0f);
    if (uPointLightEnabled) {
        result += CalcPointLight(norm, viewDir, texColor);
    }
    if (uDirLightEnabled) {
        result += CalcDirLight(norm, viewDir, texColor);
    }

    FragColor = vec4(result, 1.0);
}
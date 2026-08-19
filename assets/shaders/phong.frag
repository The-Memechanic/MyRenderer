#version 330 core
in vec3 FragPos;
in vec3 VertexColor;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D uTexture;

uniform vec3 uLightPos;
uniform vec3 uViewPos;
uniform vec3 uLightColor;

uniform float uAmbientStrength;
uniform float uSpecularStrength;
uniform float uShininess;

uniform float uLightConstant;
uniform float uLightLinear;
uniform float uLightQuadratic;

void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(uLightPos - FragPos);

    float distance = length(uLightPos - FragPos);
    float attenuation = 1.0 / (uLightConstant + uLightLinear * distance +
    uLightQuadratic * (distance * distance));

    vec3 ambient = uAmbientStrength * uLightColor;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * uLightColor;

    vec3 viewDir = normalize(uViewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), uShininess);
    vec3 specular = uSpecularStrength * spec * uLightColor;

    vec3 texColor = texture(uTexture, TexCoords).rgb;
    vec3 result = (ambient + diffuse) * attenuation * texColor + specular * attenuation;

    FragColor = vec4(result, 1.0);
}
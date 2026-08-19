#version 330 core
in vec3 FragPos;
in vec3 VertexColor;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D uTexture;

void main() {
    FragColor = texture(uTexture, TexCoords);
}
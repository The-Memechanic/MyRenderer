#version 330 core
in vec3 FragPos;
in vec3 VertexColor;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

void main() {
    // Placeholder: replace with Phong lighting once Camera/Light are wired up.
    FragColor = vec4(VertexColor, 1.0);
}
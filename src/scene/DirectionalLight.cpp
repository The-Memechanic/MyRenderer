//
// Created by memechanic on 20/08/26.
//

#include "DirectionalLight.h"
#include "render/Shader.h"

DirectionalLight::DirectionalLight(const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &color)
    : position(position), direction(direction)
{
    _color = color;
}

void DirectionalLight::ApplyToShader(const Shader &shader) const {
    shader.SetVec3("uDirLightDirection", direction);
    shader.SetVec3("uDirLightColor", _color);
    shader.SetFloat("uDirAmbientStrength", ambientStrength);
    shader.SetFloat("uDirSpecularStrength", specularStrength);
}

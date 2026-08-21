//
// Created by memechanic on 19/08/26.
//

#include "PointLight.h"
#include "render/Shader.h"

PointLight::PointLight(const glm::vec3 &position, const glm::vec3 &color)
    : position(position)
{
    _color = color;
}

void PointLight::ApplyToShader(const Shader &shader) const {
    shader.SetVec3("uLightPos", position);
    shader.SetVec3("uLightColor", _color);
    shader.SetFloat("uAmbientStrength", ambientStrength);
    shader.SetFloat("uSpecularStrength", specularStrength);
    shader.SetFloat("uLightConstant", constant);
    shader.SetFloat("uLightLinear", linear);
    shader.SetFloat("uLightQuadratic", quadratic);
}

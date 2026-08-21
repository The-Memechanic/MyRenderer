//
// Created by memechanic on 21/08/26.
//

#include "SpotLight.h"
#include "render/Shader.h"
#include <glm/gtc/matrix_transform.hpp>

SpotLight::SpotLight(const glm::vec3 &position, const glm::vec3 &direction, float innerCutoffAngle, float outerCutoffAngle, const glm::vec3 &color)
    : position(position), direction(direction), innerCutoffAngle(innerCutoffAngle), outerCutoffAngle(outerCutoffAngle)
{
    _color = color;
}

void SpotLight::ApplyToShader(const Shader &shader) const {
    shader.SetVec3("uSpotLightPos", position);
    shader.SetVec3("uSpotLightDirection", direction);
    shader.SetVec3("uSpotLightColor", _color);
    shader.SetFloat("uSpotAmbientStrength", ambientStrength);
    shader.SetFloat("uSpotSpecularStrength", specularStrength);// Spot light
    shader.SetFloat("uSpotInnerCutoff", glm::cos(glm::radians(innerCutoffAngle)));
    shader.SetFloat("uSpotOuterCutoff", glm::cos(glm::radians(outerCutoffAngle)));
    shader.SetFloat("uSpotConstant", constant);
    shader.SetFloat("uSpotLinear", linear);
    shader.SetFloat("uSpotQuadratic", quadratic);
}

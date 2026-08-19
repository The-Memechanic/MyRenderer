//
// Created by memechanic on 19/08/26.
//

#pragma once

#include "Light.h"

class PointLight final : public Light {
public:
    explicit PointLight(const glm::vec3& position, const glm::vec3& color = glm::vec3(1.0f));

    void ApplyToShader(const Shader &shader) const override;

    glm::vec3 position;

    // these are the attenuation coefficients
    // 50 units - see the Learn OpenGL point light attenuation table)
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032;
};



//
// Created by memechanic on 21/08/26.
//

#pragma once
#include "scene/light/Light.h"

class SpotLight final : public Light {
public:
    SpotLight(const glm::vec3& position, const glm::vec3& direction,
                float innerCutoffAngle = 12.5f, float outerCutoffAngle = 17.5f,
                const glm::vec3& color = glm::vec3(1.0f));

    void ApplyToShader(const Shader &shader) const override;

    glm::vec3 position;
    glm::vec3 direction;

    float innerCutoffAngle;
    float outerCutoffAngle;

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
};



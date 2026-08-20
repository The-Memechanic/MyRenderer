//
// Created by memechanic on 20/08/26.
//

#pragma once

#include "Light.h"

class DirectionalLight final : public Light {
public:
    explicit DirectionalLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color = glm::vec3(1.0f));

    void ApplyToShader(const Shader &shader) const override;

    glm::vec3 position; // only used if we want to render a light helper
    glm::vec3 direction;
};



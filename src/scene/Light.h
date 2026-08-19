//
// Created by memechanic on 19/08/26.
//

#pragma once

#include <glm/glm.hpp>

class Shader;

class Light {
public:
    virtual ~Light() = default;

    virtual void ApplyToShader(const Shader& shader) const = 0;

    glm::vec3 _color = glm::vec3(1.0f);
    float ambientStrength = 0.15f;
    float specularStrength = 0.5f;

protected:
    Light() = default;
};

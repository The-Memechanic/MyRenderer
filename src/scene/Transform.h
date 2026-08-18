//
// Created by memechanic on 18/08/26.
//
#pragma once

#include <glm/glm.hpp>

class Transform {
public:
    glm::vec3 position { 0.0f, 0.0f, 0.0f };
    glm::vec3 rotation { 0.0f, 0.0f, 0.0f };
    glm::vec3 scale { 1.0f, 1.0f, 1.0f };

    glm::mat4 GetModelMatrix() const;
};


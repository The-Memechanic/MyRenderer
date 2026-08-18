//
// Created by memechanic on 18/08/26.
//

#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Transform::GetModelMatrix() const {
    auto model = glm::mat4(1.0f);

    model = glm::translate(model, position);

    // This rotation order is a common convention but it can be however we want it
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::scale(model, scale);

    return model;
}
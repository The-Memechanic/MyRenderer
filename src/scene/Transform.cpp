//
// Created by memechanic on 18/08/26.
//

#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Transform::GetModelMatrix() const {
    const float x = glm::radians(rotation.x);
    const float y = glm::radians(rotation.y);
    const float z = glm::radians(rotation.z);

    const float cx = std::cos(x);
    const float sx = std::sin(x);

    const float cy = std::cos(y);
    const float sy = std::sin(y);

    const float cz = std::cos(z);
    const float sz = std::sin(z);

    // glm accepts matrix arguments in a column-first order (a0, a1, a2, a3, b0, b1, ...)
    // if we were to manually write down this translation matrix, it would look like this:
    //
    // 1, 0, 0, px
    // 0, 1, 0, py
    // 0, 0, 1, pz
    // 0, 0, 0, 1
    //
    // which is the correct mathematical format of the matrix

    const glm::mat4 translation(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        position.x, position.y, position.z, 1.0f
    );

    // X
    const glm::mat4 rotationX(
        1.0f, 0.0f,  0.0f, 0.0f,
        0.0f, cx,    sx,   0.0f,
        0.0f, -sx,   cx,   0.0f,
        0.0f, 0.0f,  0.0f, 1.0f
    );

    // Y
    const glm::mat4 rotationY(
        cy,   0.0f, -sy,   0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        sy,  0.0f, cy,   0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    // Z
    const glm::mat4 rotationZ(
        cz,   sz,   0.0f, 0.0f,
        -sz,  cz,   0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    const glm::mat4 scaling(
        scale.x, 0.0f,    0.0f,    0.0f,
        0.0f,     scale.y, 0.0f,    0.0f,
        0.0f,     0.0f,    scale.z, 0.0f,
        0.0f,     0.0f,    0.0f,    1.0f
    );

    return translation * rotationY * rotationX * rotationZ * scaling;
}
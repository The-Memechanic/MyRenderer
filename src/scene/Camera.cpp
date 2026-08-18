//
// Created by memechanic on 18/08/26.
//

#include "Camera.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3 position, const glm::vec3 target, const glm::vec3 up)
    : m_position(position), m_target(target), m_up(up)
{}

// We could just use glm::lookAt, but for educational purposes we build the matrix from scratch
glm::mat4 Camera::GetViewMatrix() const {
    const glm::vec3 f = glm::normalize(m_target - m_position);      // forward vector
    const glm::vec3 s = glm::normalize(glm::cross(f, m_up));    // right side
    const glm::vec3 u = glm::cross(s, f);                         // recomputed up vector

    const glm::mat4 viewMatrix(
        s.x, u.x, -f.x, 0.0f,
        s.y, u.y, -f.y, 0.0f,
        s.z, u.z, -f.z, 0.0f,
        -glm::dot(s, m_position), -glm::dot(u, m_position), glm::dot(f, m_position), 1.0f
    );

    return viewMatrix;
}

// we could also just use glm::perspective here but you know..
glm::mat4 Camera::GetProjectionMatrix(const float aspectRatio) const {
    const float tanHalfFov = std::tan(glm::radians(m_fov) * 0.5f);

    const glm::mat4 projectionMatrix(
        1.0f / (aspectRatio * tanHalfFov), 0.0f, 0.0f, 0.0f,    // aspect ratio prevents stretching in non-square screens
        0.0f, 1.0f / tanHalfFov, 0.0f, 0.0f,
        0.0f, 0.0f, -(m_far + m_near) / (m_far - m_near), -1.0f,        // this is where the depth remapping magic happens
        0.0f, 0.0f, -(2.0f * m_far * m_near) / (m_far - m_near), 0.0f   // this also contributes for depth remapping
    );

    return projectionMatrix;
}



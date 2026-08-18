//
// Created by memechanic on 18/08/26.
//

#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3 position, const glm::vec3 target, const glm::vec3 up)
    : m_position(position), m_target(target), m_up(up)
{}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(m_position, m_target, m_up);
}

glm::mat4 Camera::GetProjectionMatrix(const float aspectRatio) const {
    return glm::perspective(glm::radians(m_fov), aspectRatio, m_near, m_far);
}



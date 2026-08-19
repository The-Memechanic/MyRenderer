//
// Created by memechanic on 18/08/26.
//

#include "Camera.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

#include "glm/gtc/quaternion.hpp"

Camera::Camera(const glm::vec3 position, const float yaw, const float pitch, const glm::vec3 up)
    : m_position(position), m_worldUp(up), m_yaw(yaw), m_pitch(pitch)
{
    UpdateVectors();
}

void Camera::UpdateVectors() {
    glm::vec3 front;
    front.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
    front.y = glm::sin(glm::radians(m_pitch));
    front.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
}

// We could just use glm::lookAt, but for educational purposes we build the matrix from scratch
glm::mat4 Camera::GetViewMatrix() const {
    const glm::vec3 f = m_front;                // forward vector
    const glm::vec3 s = m_right;                // right side
    const glm::vec3 u = glm::cross(s, f);   // recomputed up vector

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

void Camera::ProcessMovement(const CameraMovement direction, const float deltaTime) {
    const float velocity = m_moveSpeed * deltaTime;

    switch (direction) {
        case CameraMovement::Forward:  m_position += m_front * velocity; break;
        case CameraMovement::Backward: m_position -= m_front * velocity; break;
        case CameraMovement::Left:     m_position -= m_right * velocity; break;
        case CameraMovement::Right:    m_position += m_right * velocity; break;
        case CameraMovement::Up:       m_position += m_worldUp * velocity; break;
        case CameraMovement::Down:     m_position -= m_worldUp * velocity; break;
    }
}

void Camera::ProcessRotation(CameraRotation direction, float deltaTime) {
    const float amount = m_rotateSpeed * deltaTime;

    switch (direction) {
        case CameraRotation::LookLeft:  m_yaw -= amount; break;
        case CameraRotation::LookRight: m_yaw += amount; break;
        case CameraRotation::LookUp:    m_pitch += amount; break;
        case CameraRotation::LookDown:  m_pitch -= amount; break;
    }

    m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f); // avoid flipping the camera
    UpdateVectors();
}



//
// Created by memechanic on 18/08/26.
//

#pragma once
#include "glm/fwd.hpp"
#include "glm/vec3.hpp"

class Camera {
public:
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix(float aspectRatio) const;

    void SetPosition(const glm::vec3& position) {m_position = position;};
    void SetTarget(const glm::vec3& target) {m_target = target;};

    glm::vec3 GetPosition() const {return m_position;}

private:
    glm::vec3 m_position;
    glm::vec3 m_target;
    glm::vec3 m_up;

    float m_fov = 45.0f; // this is degrees
    float m_near = 0.1f;
    float m_far = 100.0f;
};


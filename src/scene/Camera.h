//
// Created by memechanic on 18/08/26.
//

#pragma once
#include "glm/fwd.hpp"
#include "glm/vec3.hpp"

enum class CameraMovement { Forward, Backward, Left, Right, Up, Down };
enum class CameraRotation { LookUp, LookDown, LookLeft, LookRight };

class Camera {
public:
    explicit Camera(glm::vec3 position,
                    float yaw = -90.0f,
                    float pitch = 0.0f,
                    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix(float aspectRatio) const;

    void ProcessMovement(CameraMovement direction, float deltaTime);
    void ProcessRotation(CameraRotation direction, float deltaTime);

private:
    void UpdateVectors();

    glm::vec3 m_position;
    glm::vec3 m_front{};
    glm::vec3 m_right{};
    glm::vec3 m_worldUp;

    float m_yaw;
    float m_pitch;

    float m_moveSpeed = 3.0f;
    float m_rotateSpeed = 90.0f;

    float m_fov = 45.0f; // this is degrees
    float m_near = 0.1f;
    float m_far = 100.0f;
};


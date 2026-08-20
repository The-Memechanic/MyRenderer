//
// Created by memechanic on 18/08/26.
//

#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <chrono>
#include <thread>

#include "glm/ext/scalar_constants.hpp"

namespace {
    constexpr float kTargetFPS = 60.0f;
    constexpr float kTargetFrameTime = 1.0f / kTargetFPS; // this is in seconds
}

Application::Application()
    : m_window(1280, 720, "MyRenderer"),
      m_shader("assets/shaders/phong.vert", "assets/shaders/phong.frag"),
      m_texture("assets/textures/red-brick/red_brick_diff_1k.jpg"),
      m_mesh(Mesh::CreateCube()),
      m_camera(glm::vec3(0.0f, 0.0f, 3.0f),
                -90.0f,
                0.0f),
      m_lightShader("assets/shaders/light.vert", "assets/shaders/light.frag"),
      m_pointLight(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f)),
      m_dirLight(glm::vec3(0.0f), glm::vec3(-0.5f, -1.0f, -0.6f), glm::vec3(1.0f))
{
    m_transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    m_shader.Bind();
    m_shader.SetInt("uTexture", 0);
}

void Application::Run() {
    auto lastFrame = static_cast<float>(glfwGetTime());

    while (!m_window.ShouldClose()) {
        const auto currentFrame = static_cast<float>(glfwGetTime());
        const float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        Window::PollEvents();
        ProcessInput(deltaTime);
        Update(deltaTime);
        Render();

        m_window.SwapBuffers();

        // this makes it so that the FPS is capped at whatever value we defined
        const float frameTime = static_cast<float>(glfwGetTime()) - currentFrame;
        const float sleepTime = kTargetFrameTime - frameTime;
        if (sleepTime > 0.0f) {
            std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime));
        }
    }
}

void Application::ProcessInput(float deltaTime) {
    GLFWwindow* handle = m_window.GetHandle();

    // Movement
    if (glfwGetKey(handle, GLFW_KEY_W) == GLFW_PRESS)
        m_camera.ProcessMovement(CameraMovement::Forward, deltaTime);
    if (glfwGetKey(handle, GLFW_KEY_S) == GLFW_PRESS)
        m_camera.ProcessMovement(CameraMovement::Backward, deltaTime);
    if (glfwGetKey(handle, GLFW_KEY_A) == GLFW_PRESS)
        m_camera.ProcessMovement(CameraMovement::Left, deltaTime);
    if (glfwGetKey(handle, GLFW_KEY_D) == GLFW_PRESS)
        m_camera.ProcessMovement(CameraMovement::Right, deltaTime);
    if (glfwGetKey(handle, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_camera.ProcessMovement(CameraMovement::Up, deltaTime);
    if (glfwGetKey(handle, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        m_camera.ProcessMovement(CameraMovement::Down, deltaTime);

    // Rotation
    if (glfwGetKey(handle, GLFW_KEY_UP) == GLFW_PRESS)
        m_camera.ProcessRotation(CameraRotation::LookUp, deltaTime);
    if (glfwGetKey(handle, GLFW_KEY_DOWN) == GLFW_PRESS)
        m_camera.ProcessRotation(CameraRotation::LookDown, deltaTime);
    if (glfwGetKey(handle, GLFW_KEY_LEFT) == GLFW_PRESS)
        m_camera.ProcessRotation(CameraRotation::LookLeft, deltaTime);
    if (glfwGetKey(handle, GLFW_KEY_RIGHT) == GLFW_PRESS)
        m_camera.ProcessRotation(CameraRotation::LookRight, deltaTime);

    if (glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(handle, true);
}

void Application::Update(const float deltaTime) {
    // matrix expects input rotation in degrees
    // rotate it a little to see more faces
    m_transform.rotation.x = 0.0f;
    m_transform.rotation.y = -20.0f;
    //m_transform.rotation.z += 50.0f * deltaTime; // funky rotation woah!

    // point light showcase
    constexpr float radius = 1.0f;
    constexpr float rotationSpeed = 3.0f;
    m_lightTransform.scale = glm::vec3(0.2f);
    m_lightTransform.position.x = radius * glm::cos(rotationSpeed * m_time);
    m_lightTransform.position.z = radius * glm::sin(rotationSpeed * m_time);
    m_lightTransform.position.y = glm::cos(rotationSpeed * 0.5f * m_time);

    // this is an attempt to recreate the vibe of the Toyota Yaris meme :)
    constexpr float y_variance = 0.2f;
    constexpr float xz_variance = 0.3f;
    constexpr float wobble_velocity = 13.0f;
    m_transform.scale.y = 1.0f + y_variance * glm::sin(wobble_velocity * m_time);
    m_transform.scale.x = 1.0f + xz_variance * glm::sin(-wobble_velocity * m_time);
    m_transform.scale.z = 1.0f + xz_variance * glm::sin(-wobble_velocity * m_time);
    m_transform.position.y = y_variance * 0.5f * glm::sin(wobble_velocity * m_time);
    //m_transform.position.z = 2.0f * glm::sin(wobble_velocity * 0.5f * m_time);

    m_pointLight.position = m_lightTransform.position;  // update the actual light position alongside the helper
    m_time += deltaTime;
}

void Application::Render() const {
    glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader.Bind();
    m_texture.Bind(0);

    // lights
    constexpr bool hasPointLight = true;
    constexpr bool hasDirLight = true;

    m_shader.SetBool("uPointLightEnabled", hasPointLight);
    m_shader.SetBool("uDirLightEnabled", hasDirLight);
    if (hasPointLight) m_pointLight.ApplyToShader(m_shader);
    if (hasDirLight) m_dirLight.ApplyToShader(m_shader);

    // the cube
    m_shader.SetMat4("uModel", m_transform.GetModelMatrix());
    m_shader.SetMat4("uView", m_camera.GetViewMatrix());
    m_shader.SetMat4("uProjection", m_camera.GetProjectionMatrix(1280.0f / 720.0f));
    m_shader.SetVec3("uViewPos", m_camera.GetPosition());
    m_shader.SetFloat("uShininess", 32.0f);
    m_mesh.Draw();

    // point light helper
    m_lightShader.Bind();
    m_lightShader.SetMat4("uModel", m_lightTransform.GetModelMatrix());
    m_lightShader.SetMat4("uView", m_camera.GetViewMatrix());
    m_lightShader.SetMat4("uProjection", m_camera.GetProjectionMatrix(1280.0f / 720.0f));
    m_lightShader.SetVec3("uLightColor", m_pointLight._color);
    m_mesh.Draw();
}

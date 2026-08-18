//
// Created by memechanic on 18/08/26.
//

#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <chrono>
#include <thread>

namespace {
    constexpr float kTargetFPS = 60.0f;
    constexpr float kTargetFrameTime = 1.0f / kTargetFPS; // this is in seconds
}

Application::Application()
    : m_window(1280, 720, "MyRenderer"),
      m_shader("assets/shaders/basic.vert", "assets/shaders/basic.frag"),
      m_mesh(Mesh::CreateCube()),
      m_camera(glm::vec3(0.0f, 0.0f, 3.0f),
                glm::vec3(0.0f, 0.0f, 0.0f))
{
    m_transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
}

void Application::Run() {
    float lastFrame = static_cast<float>(glfwGetTime());

    while (!m_window.ShouldClose()) {
        const float currentFrame = static_cast<float>(glfwGetTime());
        const float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessInput();
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

void Application::ProcessInput() {
    Window::PollEvents();
}

void Application::Update(const float deltaTime) {
    // matrix expects input rotation in degrees
    m_transform.rotation.x = 10.0f;
    m_transform.rotation.y = -20.0f;
    m_transform.rotation.z += 50.0f * deltaTime;
    m_transform.scale.y = 1.0f + 0.5f * glm::sin(10.0f * m_time);
    m_transform.scale.x = 1.0f + 0.5f * glm::sin(-10.0f * m_time);

    m_time += deltaTime;
}

void Application::Render() const {
    glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader.Bind();

    m_shader.SetMat4("uModel", m_transform.GetModelMatrix());
    m_shader.SetMat4("uView", m_camera.GetViewMatrix());
    m_shader.SetMat4("uProjection", m_camera.GetProjectionMatrix(1280.0f / 720.0f));

    m_mesh.Draw();
}

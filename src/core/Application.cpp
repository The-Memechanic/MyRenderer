//
// Created by memechanic on 18/08/26.
//

#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

Application::Application()
    : m_window(1280, 720, "MyRenderer"),
      m_shader("assets/shaders/basic.vert", "assets/shaders/basic.frag"),
      m_mesh(Mesh::CreateCube())
{
    m_transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
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
    }
}

void Application::ProcessInput() {
    Window::PollEvents();
}

void Application::Update(const float deltaTime) {
    m_transform.rotation.y += 60.0f * deltaTime;
    m_transform.rotation.x += 30.0f * deltaTime;
}

void Application::Render() const {
    glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader.Bind();

    m_shader.SetMat4("uModel", m_transform.GetModelMatrix());
    m_shader.SetMat4("uView", glm::mat4(1.0f));
    m_shader.SetMat4("uProjection", glm::mat4(1.0f));

    m_mesh.Draw();
}

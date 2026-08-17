#include <glad/glad.h>
#include "core/Window.h"
#include "render/Shader.h"
#include "render/Mesh.h"

#include <iostream>

int main() {
    try {
        const Window window(1280, 720, "MyRenderer");

        const Shader shader("assets/shaders/basic.vert", "assets/shaders/basic.frag");
        const Mesh triangle = Mesh::CreateTriangle();

        while (!window.ShouldClose()) {
            Window::PollEvents();

            glClearColor(0.10f, 0.10f, 0.12f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader.Bind();
            shader.SetMat4("uModel", glm::mat4(1.0f));
            shader.SetMat4("uView", glm::mat4(1.0f));
            shader.SetMat4("uProjection", glm::mat4(1.0f));
            triangle.Draw();

            window.SwapBuffers();
        }
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
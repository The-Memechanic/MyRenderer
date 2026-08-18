//
// Created by memechanic on 18/08/26.
//

#pragma once

#include "core/Window.h"
#include "render/Shader.h"
#include "render/Mesh.h"
#include "scene/Transform.h"
#include "scene/Camera.h"

class Application {
public:
    Application();
    ~Application() = default;

    void Run();

private:
    static void ProcessInput();
    void Update(float deltaTime);
    void Render() const;

    Window m_window;
    Shader m_shader;
    Mesh m_mesh;

    Transform m_transform;
    Camera m_camera;
    float m_time = 0.0f;
};


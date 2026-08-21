//
// Created by memechanic on 18/08/26.
//

#pragma once

#include "core/Window.h"
#include "render/Shader.h"
#include "render/Mesh.h"
#include "render/Texture.h"
#include "scene/Transform.h"
#include "scene/Camera.h"
#include "scene/light/PointLight.h"
#include "scene/light/DirectionalLight.h"
#include "scene/light/SpotLight.h"

class Application {
public:
    Application();
    ~Application() = default;

    void Run();

private:
    void ProcessInput(float deltaTime);
    void Update(float deltaTime);
    void Render() const;

    Window m_window;
    Shader m_shader;
    Texture m_texture;
    Mesh m_mesh;

    Transform m_transform;
    Transform m_lightTransform;
    Camera m_camera;
    Shader m_lightShader;
    PointLight m_pointLight;
    DirectionalLight m_dirLight;
    SpotLight m_spotLight;

    float m_time = 0.0f;
};


//
// Created by memechanic on 17/08/26.
//

#pragma once

#include <glm/glm.hpp>
#include <vector>

// Matches the attribute layout in assets/shaders/basic.vert:
//   location 0 -> position
//   location 1 -> normal
//   location 2 -> texcoords
//   location 3 -> color
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Color;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    void Draw() const;

    // Hardcoded single-triangle mesh, useful as the very first thing to get
    // on screen before real geometry/model loading exists.
    static Mesh CreateTriangle();

private:
    unsigned int m_Vao = 0;
    unsigned int m_Vbo = 0;
    unsigned int m_Ebo = 0;
    unsigned int m_IndexCount = 0;

    void SetupMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
};
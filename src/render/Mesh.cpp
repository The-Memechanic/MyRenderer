//
// Created by memechanic on 17/08/26.
//

#include "Mesh.h"

#include <glad/glad.h>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
    SetupMesh(vertices, indices);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &m_Vao);
    glDeleteBuffers(1, &m_Vbo);
    glDeleteBuffers(1, &m_Ebo);
}

void Mesh::SetupMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
    m_IndexCount = static_cast<unsigned int>(indices.size());

    glGenVertexArrays(1, &m_Vao);
    glGenBuffers(1, &m_Vbo);
    glGenBuffers(1, &m_Ebo);

    glBindVertexArray(m_Vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<long>(vertices.size() * sizeof(Vertex)),
                 vertices.data(),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 static_cast<long>(indices.size() * sizeof(unsigned int)),
                 indices.data(),
                 GL_STATIC_DRAW);

    // location 0: position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                           reinterpret_cast<void*>(offsetof(Vertex, Position)));

    // location 1: color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                           reinterpret_cast<void*>(offsetof(Vertex, Color)));

    // location 2: normal
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                           reinterpret_cast<void*>(offsetof(Vertex, Normal)));

    // location 3: texcoords
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                           reinterpret_cast<void*>(offsetof(Vertex, TexCoords)));

    glBindVertexArray(0);
}

void Mesh::Draw() const {
    glBindVertexArray(m_Vao);
    glDrawElements(GL_TRIANGLES, static_cast<int>(m_IndexCount), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

Mesh Mesh::CreateTriangle() {
    // Normal is irrelevant for a flat unlit triangle right now, but the
    // attribute slot has to be filled since the shader/VAO layout expects
    // it. Pointing it along +Z keeps it sane once lighting is added later.
    const std::vector<Vertex> vertices = {
        // position, color, normal, tex
        { {  0.0f,  0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.5f, 1.0f } }, // top: red
        { { -0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } }, // bottom-left: green
        { {  0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } }, // bottom-right: blue
    };

    const std::vector<unsigned int> indices = { 0, 1, 2 };

    return {vertices, indices};
}
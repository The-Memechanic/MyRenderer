//
// Created by memechanic on 19/08/26.
//

#include "Texture.h"

#include <glad/glad.h>
#include <stb_image.h>

#include <iostream>
#include <stdexcept>

Texture::Texture(const std::string &path, bool flipVertically) {
    LoadFromFile(path, flipVertically);
}

Texture::~Texture() {
    if (m_id != 0) {
        glDeleteTextures(1, &m_id);
    }
}

Texture::Texture(Texture &&other) noexcept
    : m_id(other.m_id), m_width(other.m_width), m_height(other.m_height), m_channels(other.m_channels)
{
    other.m_id = 0;
}

Texture &Texture::operator=(Texture &&other) noexcept {
    if (this != &other) {
        if (m_id != 0) {
            glDeleteTextures(1, &m_id);
        }
        m_id = other.m_id;
        m_width = other.m_width;
        m_height = other.m_height;
        m_channels = other.m_channels;
        other.m_id = 0;
    }
    return *this;
}

void Texture::LoadFromFile(const std::string &path, bool flipVertically) {
    stbi_set_flip_vertically_on_load(flipVertically);

    int width, height, channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (!data) {
        throw std::runtime_error("Failed to load texture: " + path);
    }

    m_width = width;
    m_height = height;
    m_channels = channels;

    GLenum internalFormat;
    GLenum dataFormat;
    switch (channels) {
        case 1: internalFormat = dataFormat = GL_RED; break;
        case 3: internalFormat = dataFormat = GL_RGB; break;
        case 4: internalFormat = dataFormat = GL_RGBA; break;
        default:
            stbi_image_free(data);
            throw std::runtime_error("Unsupported channel count (" + std::to_string(channels) + ") in texture: " + path);
    }

    // communicating with OpenGL to create the texture (this looks crazy)
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(internalFormat), width, height, 0,
                 dataFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);

    std::cout << "Loaded texture \"" << path << "\" (" << m_width << "x" << m_height << ", " << m_channels << " channels)\n";
}

void Texture::Bind(const unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::Unbind(const unsigned int unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, 0);
}

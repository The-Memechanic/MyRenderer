//
// Created by memechanic on 19/08/26.
//

#pragma once

#include <string>

class Texture {
public:
    Texture() = default;
    explicit Texture(const std::string& path, bool flipVertically = true);
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    void Bind(unsigned int unit = 0) const;
    static void Unbind(unsigned int unit = 0);

    unsigned int GetId() const { return m_id; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }

private:
    void LoadFromFile(const std::string& path, bool flipVertically);

    unsigned int m_id = 0;
    int m_width = 0;
    int m_height = 0;
    int m_channels = 0;
};



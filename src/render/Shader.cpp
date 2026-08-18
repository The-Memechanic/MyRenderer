#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

std::string Shader::ReadFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open shader file: " + path);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int Shader::CompileStage(unsigned int stageType, const std::string& source, const std::string& debugName) {
    unsigned int shader = glCreateShader(stageType);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cerr << "Shader compilation failed (" << debugName << "):\n" << infoLog << std::endl;
        throw std::runtime_error("Shader compilation failed: " + debugName);
    }
    return shader;
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    const std::string vertexSrc = ReadFile(vertexPath);
    const std::string fragmentSrc = ReadFile(fragmentPath);

    const unsigned int vertexShader = CompileStage(GL_VERTEX_SHADER, vertexSrc, vertexPath);
    const unsigned int fragmentShader = CompileStage(GL_FRAGMENT_SHADER, fragmentSrc, fragmentPath);

    m_ProgramId = glCreateProgram();
    glAttachShader(m_ProgramId, vertexShader);
    glAttachShader(m_ProgramId, fragmentShader);
    glLinkProgram(m_ProgramId);

    int success;
    glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(m_ProgramId, 1024, nullptr, infoLog);
        std::cerr << "Shader linking failed:\n" << infoLog << std::endl;
        throw std::runtime_error("Shader program linking failed");
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(m_ProgramId);
}

void Shader::Bind() const {
    glUseProgram(m_ProgramId);
}

void Shader::SetBool(const std::string& name, const bool value) const {
    glUniform1i(glGetUniformLocation(m_ProgramId, name.c_str()), static_cast<int>(value));
}

void Shader::SetInt(const std::string& name, const int value) const {
    glUniform1i(glGetUniformLocation(m_ProgramId, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, const float value) const {
    glUniform1f(glGetUniformLocation(m_ProgramId, name.c_str()), value);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(m_ProgramId, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value) const {
    glUniformMatrix4fv(glGetUniformLocation(m_ProgramId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

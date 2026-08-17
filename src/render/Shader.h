#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    // Paths to a vertex and fragment shader source file, e.g.
    // "assets/shaders/basic.vert", "assets/shaders/basic.frag"
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Bind() const;

    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec3(const std::string& name, const glm::vec3& value) const;
    void SetMat4(const std::string& name, const glm::mat4& value) const;

private:
    unsigned int m_ProgramId = 0;

    static std::string ReadFile(const std::string& path);
    static unsigned int CompileStage(unsigned int stageType, const std::string& source, const std::string& debugName);
};

#pragma once

#include <string>

struct GLFWwindow;

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool ShouldClose() const;

    static void PollEvents();
    void SwapBuffers() const;

    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    GLFWwindow* GetHandle() const { return m_Handle; }

private:
    GLFWwindow* m_Handle = nullptr;
    int m_Width;
    int m_Height;
};

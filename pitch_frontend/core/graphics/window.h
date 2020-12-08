#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

class Window
{
public:
    Window(int width, int height, const std::string& title);
    Window(const Window&) = delete;
    Window(Window&&) = delete;
    ~Window();

    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) = delete;

    void beginFrame() noexcept;
    void endFrame() noexcept;

    bool isOpen() const noexcept;
    void close() noexcept;

private:
    static void onResize(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow* window);

private:
    GLFWwindow* window_;
    int width_;
    int height_;
};

#endif //WINDOW_H

#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "color.h"

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

    void setBackgroundColor(const Color& color);

    //NOTE(asoelter): This is a debug function for
    //integrating imgui. Should be removed once
    //imgui is settled
    GLFWwindow* glfwWindow() { return window_; }

private:
    static void onResize(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow* window);

private:
    GLFWwindow* window_;
    int         width_;
    int         height_;
    Color       backgroundColor_;
};

#endif //WINDOW_H

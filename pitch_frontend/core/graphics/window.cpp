#include "window.h"

#include <cassert>

Window::Window(int width, int height, const std::string& title)
    : window_(nullptr)
    , width_(width)
    , height_(height)
    , backgroundColor_(Color::black())
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if(!window_)
    {
        assert(false);
    }

    glfwMakeContextCurrent(window_);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        assert(false);
    } 

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window_, onResize);
    glfwSetWindowUserPointer(window_, this);
}

Window::~Window()
{
    if(window_)
    {
        glfwDestroyWindow(window_);
    }

    //This means we only support one window, consider
    //if that is what we actually want
    glfwTerminate(); 
}

void Window::beginFrame() noexcept
{
    processInput(window_);
    glClearColor(backgroundColor_.r(), backgroundColor_.g(), backgroundColor_.b(), backgroundColor_.a());
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::endFrame() noexcept
{
    assert(window_);
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

bool Window::isOpen() const noexcept
{
    assert(window_);
    bool result = !glfwWindowShouldClose(window_);
    return result;
}

void Window::close() noexcept
{
    assert(window_);
    glfwSetWindowShouldClose(window_, true);
}

void Window::setBackgroundColor(const Color& color)
{
    backgroundColor_ = color;
}

void Window::onResize(GLFWwindow* window, int width, int height)
{
    assert(window);
    Window* windowObject = static_cast<Window*>(glfwGetWindowUserPointer(window));
    windowObject->width_ = width;
    windowObject->height_ = height;
    glViewport(0, 0, width, height);
}

void Window::processInput(GLFWwindow* window)
{
    assert(window);
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

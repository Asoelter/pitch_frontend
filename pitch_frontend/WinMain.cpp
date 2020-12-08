#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#   define NOMINMAX
#endif

#include <string>
#include <Windows.h>

#include <covid/socket.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/graphics/vertex_array_object.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void MsgBox(const char* title, const char* message)
{
    MessageBox(NULL, message, title, NULL);
}

void onResize(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

INT WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR lpCmdLine,
    INT nCmdShow)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Pitch", nullptr, nullptr);

    if(!window)
    {
        MsgBox("Error", "Failed to create window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        MsgBox("Error", "Failed to load glad");
        return -1;
    } 

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, onResize);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    VertexArrayObject vao;

    //Vertex buffer object code
    unsigned vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Vertex Shader code
    const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 pos;\n"
        "layout (location = 1) in vec3 vertexColor;\n"
        "out vec3 fragmentColor;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(pos, 1.0);\n"
        "   fragmentColor = vertexColor;\n"
        "}\0";

    const auto vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShaderId);

    int success = 0;
    char infoLog[512];
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShaderId, 512, nullptr, infoLog);
        const auto errorMessage = std::string("Vertex shader failed to compile: ") + infoLog;
        MsgBox("Vertex shader failed to compile", errorMessage.c_str());
    }

    //Fragment shader code
    const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 outColor;\n"
        "in vec3 fragmentColor;\n"
        "void main()\n"
        "{\n"
        "   outColor = vec4(fragmentColor, 1.0f);\n"
        "}\0";

    const auto fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShaderId);

    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShaderId, 512, nullptr, infoLog);
        const auto errorMessage = std::string("Fragment shader failed to compile: ") + infoLog;
        MsgBox("Fragment shader failed to compile", errorMessage.c_str());
    }

    //Shader program code
    const auto shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertexShaderId);
    glAttachShader(shaderProgramId, fragmentShaderId);
    glLinkProgram(shaderProgramId);
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shaderProgramId, 512, nullptr, infoLog);
        const auto errorMessage = std::string("Shader program failed to link: ") + infoLog;
        MsgBox("Shader program failed to link", errorMessage.c_str());
    }

    //6 * sizeof(float) = size in bytes until the next vertex attribute of the same type
    //(void*)(3 * sizeof(float) = how far this index is away from the start
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr); //applies to most recently bound vbo
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); //applies to most recently bound vbo
    glEnableVertexAttribArray(1);

    //Texture code
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int textureWidth;
    int textureHeight;
    int channelCount;
    const auto filePath = "../../../../pitch_frontend/res/textures/king_of_hearts.jpg";
    unsigned char* textureData = stbi_load(filePath, &textureWidth, &textureHeight, &channelCount, 0);

    if(!textureData)
    {
        MsgBox("error", "Failed to load texture data");
        return -1;
    }

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramId);
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    glfwTerminate();

    return 0;
}

void onResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

#if 0
INT WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR lpCmdLine,
    INT nCmdShow)
{
    auto window = gui::Window(math::Rectangle::defaultPosition(700, 400), "Pitch");
    auto createButton = gui::Button(gui::Button::Descriptor(230, 100, 200, 90, "Create"));
    connect(createButton.pushed, Slot<>([]() {MsgBox("pushed", "pushed"); }));
    window.attach(std::move(createButton));

    auto renderer = Renderer(window);
    auto camera = firstQuadOrthoCamera(8.0f, 8.0f, 2.0f);

    std::vector vertices =
    {
        PVertex{DirectX::XMFLOAT4{ 2.0f, 4.0f, 1.0f, 1.0f}},
        PVertex{DirectX::XMFLOAT4{ 4.0f, 0.0f, 1.0f, 1.0f}},
        PVertex{DirectX::XMFLOAT4{ 0.0f, 0.0f, 1.0f, 1.0f}}
    };
    auto vshader = VertexShader(shaderSource(L"solid_vertex.hlsl"));
    auto pshader = PixelShader(shaderSource(L"solid_pixel.hlsl"));
    renderer.bindVertexShader(vshader);
    renderer.bindPixelShader(pshader);

    Color color = Color::LightGrey();

    Mesh mesh(vertices);

    connect(gui::Keyboard::upArrowKeyPressed,    Slot<>([&mesh]() {mesh.translate(0.0f, 0.03f); }));
    connect(gui::Keyboard::rightArrowKeyPressed, Slot<>([&mesh]() {mesh.translate(0.03f, 0.0f); }));
    connect(gui::Keyboard::downArrowKeyPressed,  Slot<>([&mesh]() {mesh.translate(0.0f, -0.03f); }));
    connect(gui::Keyboard::leftArrowKeyPressed,  Slot<>([&mesh]() {mesh.translate(-0.03f, 0.0f); }));

    while(window.isOpen())
    {
        window.update();
        renderer.beginFrame(color);
        renderer.bindCamera(camera);
        renderer.draw(mesh);
        renderer.endFrame();
    }

    return 0;
}
#endif

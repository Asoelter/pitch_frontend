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
#include "core/graphics/vertex_buffer_object.h"
#include "core/graphics/window.h"

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
#if 0
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
#endif

    Window window(800, 600, "Pitch");

    std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, //bottom left
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, //bottom right
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, //top left

         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, //bottom right
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, //top right
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f //top left
    };

    std::vector<unsigned> valuesPerAttribute = { 3, 2 };

    VertexArrayObject vao;
    VertexBufferObject bestVbo(vertices, valuesPerAttribute);

    //Vertex Shader code
    const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 pos;\n"
        "layout (location = 1) in vec2 vertTextureCoords;\n"
        "\n"
        "out vec2 fragTextureCoords;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(pos, 1.0);\n"
        "   fragTextureCoords = vertTextureCoords;\n"
        "}";

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
        "in vec2 fragTextureCoords;\n"
        "uniform sampler2D fragTexture;\n"
        "void main()\n"
        "{\n"
        "   outColor = texture(fragTexture, fragTextureCoords);\n"
        "}";

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

    //Texture code
    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int textureWidth;
    int textureHeight;
    int channelCount;
    const auto filePath = "../../../../pitch_frontend/res/textures/king_of_hearts.png";
    unsigned char* textureData = stbi_load(filePath, &textureWidth, &textureHeight, &channelCount, 0);

    if(!textureData)
    {
        MsgBox("error", "Failed to load texture data");
        return -1;
    }

    //NOTE: Use GL_GRBA to png files, GL_GRB for jpg
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(textureData);

    while(window.isOpen())
    {
        window.beginFrame();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);

        window.endFrame();
    }

#if 0
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
#endif

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

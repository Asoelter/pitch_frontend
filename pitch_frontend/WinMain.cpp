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

#include "core/graphics/shader.h"
#include "core/graphics/shader_program.h"
#include "core/graphics/vertex_array_object.h"
#include "core/graphics/vertex_buffer_object.h"
#include "core/graphics/window.h"

#include "core/util/file_io.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void MsgBox(const char* title, const char* message)
{
    MessageBox(NULL, message, title, NULL);
}

INT WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR lpCmdLine,
    INT nCmdShow)
{
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
    VertexBufferObject vbo(vertices, valuesPerAttribute);

    VertexShader vertexShader(
        "#version 330 core\n"
        "layout (location = 0) in vec3 pos;\n"
        "layout (location = 1) in vec2 vertTextureCoords;\n"
        "\n"
        "out vec2 fragTextureCoords;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(pos, 1.0);\n"
        "   fragTextureCoords = vertTextureCoords;\n"
        "}"
    );

    FragmentShader fragmentShader(
        "#version 330 core\n"
        "out vec4 outColor;\n"
        "in vec2 fragTextureCoords;\n"
        "uniform sampler2D fragTexture;\n"
        "void main()\n"
        "{\n"
        "   outColor = texture(fragTexture, fragTextureCoords);\n"
        "}"
    );

    ShaderProgram program(std::move(vertexShader), std::move(fragmentShader));
# if 0
    //Shader program code
    const auto shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertexShader.id());
    glAttachShader(shaderProgramId, fragmentShader.id());
    glLinkProgram(shaderProgramId);
    glDeleteShader(vertexShader.id());
    glDeleteShader(fragmentShader.id());

    int success;
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);

    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shaderProgramId, 512, nullptr, infoLog);
        const auto errorMessage = std::string("Shader program failed to link: ") + infoLog;
        MsgBox("Shader program failed to link", errorMessage.c_str());
    }
#endif

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

    //NOTE: Use GL_GRBA for png files, GL_GRB for jpg
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(textureData);

    while(window.isOpen())
    {
        window.beginFrame();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //glUseProgram(shaderProgramId);
        program.bind();
        glBindTexture(GL_TEXTURE_2D, textureId);
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);

        window.endFrame();
    }

    return 0;
}

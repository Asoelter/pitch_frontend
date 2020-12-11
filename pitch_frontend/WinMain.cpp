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
#include "core/graphics/texture.h"
#include "core/graphics/vertex_array_object.h"
#include "core/graphics/vertex_buffer_object.h"
#include "core/graphics/window.h"

#include "core/util/file_io.h"

#ifdef FREE_CODE
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#else
#include "util/file_io.h"
#endif

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

    const std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, //bottom left
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, //bottom right
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, //top left

         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, //bottom right
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, //top right
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f //top left
    };

    const std::vector<unsigned> valuesPerAttribute = { 3, 2 };

    VertexArrayObject vao;
    VertexBufferObject vbo(vertices, valuesPerAttribute);

    VertexShader vertexShader(readFile("../../../../pitch_frontend/res/shaders/position_texture_vertex.glsl"));
    FragmentShader fragmentShader(readFile("../../../../pitch_frontend/res/shaders/position_texture_fragment.glsl"));
    ShaderProgram program(std::move(vertexShader), std::move(fragmentShader));

#if 0
    //Texture code
    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    const auto filePath = "../../../../pitch_frontend/res/textures/king_of_hearts.png";
    const auto textureInfo = loadTextureInfo(filePath);

    //NOTE: Use GL_GRBA for png files, GL_GRB for jpg
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureInfo.width, textureInfo.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureInfo.data);
    glGenerateMipmap(GL_TEXTURE_2D);
#endif

    const auto filePath = "../../../../pitch_frontend/res/textures/king_of_hearts.png";
    const auto textureInfo = loadTextureInfo(filePath);
    auto texture = Texture(textureInfo);

    while(window.isOpen())
    {
        window.beginFrame();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.bind();
        //glBindTexture(GL_TEXTURE_2D, textureId);
        texture.bind();
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);

        window.endFrame();
    }

    return 0;
}

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


#include "core/container/typelist.h"

#include "core/graphics/renderer.h"
#include "core/graphics/shader.h"
#include "core/graphics/shader_program.h"
#include "core/graphics/texture.h"
#include "core/graphics/vertex_array_object.h"
#include "core/graphics/vertex_buffer_object.h"
#include "core/graphics/window.h"

#include "core/math/vec.h"
#include "core/math/mat.h"

#include "core/util/file_io.h"

INT WinMain(HINSTANCE hInstance,
            HINSTANCE hPrevInstance,
            PSTR      lpCmdLine,
            INT       nCmdShow)
{

    Window window(800, 600, "Pitch");
    window.setBackgroundColor(Color(0.2f, 0.3f, 0.3f, 1.0f));


    const std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, //bottom left
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, //bottom right
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, //top left

         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, //bottom right
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, //top right
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  //top left
    };

    const std::vector<unsigned> valuesPerAttribute = { 3, 2 };

    VertexArrayObject vao;
    VertexBufferObject vbo(vertices, valuesPerAttribute);

    VertexShader vertexShader(readFile("../../../../pitch_frontend/res/shaders/position_texture_vertex.glsl"));
    FragmentShader fragmentShader(readFile("../../../../pitch_frontend/res/shaders/position_texture_fragment.glsl"));
    ShaderProgram program(std::move(vertexShader), std::move(fragmentShader));

    const auto filePath = "../../../../pitch_frontend/res/textures/king_of_hearts.png";
    const auto textureInfo = loadTextureInfo(filePath);
    auto texture = Texture(textureInfo);
    float angle = 0.0f;
    float cameraX = 0.0f;
    Renderer renderer;

    while(window.isOpen())
    {
        window.beginFrame();

        program.bind();
        const auto rotation = Mat4::rotate(Vec4(0.0f, 0.0f, 1.0f, 1.0f), Degree(angle));
        program.setUniform("rotation", rotation);
        texture.bind();
        vao.bind();
        renderer.render(vbo);

        window.endFrame();

        angle += 0.03f;
        cameraX += 0.0001f;

        if(cameraX > 1.0f)
        {
            cameraX = -1.0f;
        }
    }

    return 0;
}

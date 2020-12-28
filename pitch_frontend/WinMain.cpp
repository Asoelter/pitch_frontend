#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#   define NOMINMAX
#endif

#include <Windows.h>

#include <covid/socket.h>

#include "core/graphics/camera.h"
#include "core/graphics/mesh.h"
#include "core/graphics/renderer.h"
#include "core/graphics/shader.h"
#include "core/graphics/shader_program.h"
#include "core/graphics/vertex_array_object.h"
#include "core/graphics/window.h"

#include "core/math/vec.h"

#include "core/util/resource_loader.h"

#include "game/card.h"
#include "game/start_menu.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

INT WinMain(HINSTANCE hInstance,
            HINSTANCE hPrevInstance,
            PSTR      lpCmdLine,
            INT       nCmdShow)
{

    Window window(800, 600, "Pitch");
    window.setBackgroundColor(Color(0.2f, 0.3f, 0.3f, 1.0f));

    VertexArrayObject vao;

    VertexShader vertexShader(ResourceLoader::loadShader("position_texture_vertex.glsl"));
    FragmentShader fragmentShader(ResourceLoader::loadShader("position_texture_fragment.glsl"));
    ShaderProgram program(std::move(vertexShader), std::move(fragmentShader));

    Renderer renderer;
    Camera camera(Camera::Orientation::normalOrientation(0.3f), {0.0f, 20.0f, 0.0f, 20.0f, -20.0f, 20.0f});

    Card twoOfDiamonds(Card::Suit::Diamond, Card::Number::Two);
    twoOfDiamonds.translate({ 5.0f, 5.0f, 0.0f });

    Card card(Card::Suit::Heart, Card::Number::Queen);
    card.translate({ 10.0f, 10.0f, 0.0f });

    bool playingGame = true;
    StartMenu startMenu(window);

    while(window.isOpen())
    {
        window.beginFrame();

        if (playingGame)
        {
            program.bind();
            program.setUniform("model", card.mesh().matrix());
            program.setUniform("view", camera.view());
            program.setUniform("projection", camera.projection());
            //vao.bind();
            card.prepareToRender();
            renderer.render(card.mesh());

            program.bind();
            program.setUniform("model", twoOfDiamonds.mesh().matrix());
            program.setUniform("view", camera.view());
            program.setUniform("projection", camera.projection());
            //vao.bind();
            twoOfDiamonds.prepareToRender();
            renderer.render(twoOfDiamonds.mesh());
        }

        startMenu.show();

        window.endFrame();
    }

    return 0;
}

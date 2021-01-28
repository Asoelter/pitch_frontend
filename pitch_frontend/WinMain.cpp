#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#   define NOMINMAX
#endif

#include <Windows.h>

#include "core/graphics/camera.h"
#include "core/graphics/mesh.h"
#include "core/graphics/renderer.h"
#include "core/graphics/shader.h"
#include "core/graphics/shader_program.h"
#include "core/graphics/vertex_array_object.h"
#include "core/graphics/window.h"

#include "core/math/vec.h"

#include "core/util/resource_loader.h"

#include "game/bid_menu.h"
#include "game/card.h"
#include "game/start_menu.h"
#include "game/socket_thread.h"

#include "messages.h"

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

    Card twoOfDiamonds(CardSuit::Diamond, CardNumber::Two);
    twoOfDiamonds.translate({ 5.0f, 5.0f, 0.0f });

    Card card(CardSuit::Heart, CardNumber::Queen);
    card.translate({ 10.0f, 10.0f, 0.0f });

    StartMenu startMenu(window);

    while(window.isOpen() && !startMenu.userHasSubmitted())
    {
        window.beginFrame();
        startMenu.show();
        window.endFrame();
    }

    auto socketThread = SocketThread(startMenu.ipAddress(), startMenu.portNumber());
    socketThread.sendMessage(PlayerReadyMessage());
    std::vector<std::optional<Card>> hand;
    BidMenu bidMenu;
    bool showBidMenu = false;

    while(window.isOpen())
    {
        window.beginFrame();

        program.bind();
        program.setUniform("model", card.mesh().matrix());
        program.setUniform("view", camera.view());
        program.setUniform("projection", camera.projection());
        vao.bind();
        card.prepareToRender();
        renderer.render(card.mesh());

        program.bind();
        program.setUniform("model", twoOfDiamonds.mesh().matrix());
        program.setUniform("view", camera.view());
        program.setUniform("projection", camera.projection());
        vao.bind();
        twoOfDiamonds.prepareToRender();
        renderer.render(twoOfDiamonds.mesh());

        int index = 0;
        constexpr auto padBetweenCards = 0.1f;

        for(auto& cardInHand : hand)
        {
            if(cardInHand)
            {
                constexpr auto originalXOffset = 2.0f;
                const auto xOffset = originalXOffset + ((index) * (Card::width / 2.0f)) + (index * padBetweenCards);
                const auto yOffset = (camera.ymax() + camera.ymin()) / 2.0f;
                cardInHand->setPosition({xOffset, yOffset});
                ++index;
                program.bind();
                program.setUniform("model", cardInHand->mesh().matrix());
                program.setUniform("view", camera.view());
                program.setUniform("projection", camera.projection());
                vao.bind();
                cardInHand->prepareToRender();
                renderer.render(cardInHand->mesh());
            }
        }

        if(showBidMenu)
        {
            bidMenu.setHand(hand);
            bidMenu.show();
        }

        window.endFrame();

        const auto message = socketThread.message();

        if(message)
        {
            const auto messageId = std::visit(ExtractId{}, message.value());

            switch(messageId)
            {
                case MessageId::PlayerReady:            break;
                case MessageId::AcknowledgePlayerReady: break;
                case MessageId::PlayedCard:
                {
                    auto messageVariant = message.value();
                    auto playedCardMessage = std::get_if<PlayedCardMessage>(&messageVariant);

                    if(playedCardMessage)
                    {
                        hand.push_back(Card(playedCardMessage->suit, playedCardMessage->number));
                    }
                }break;
                case MessageId::PromptBid:
                {
                    showBidMenu = true;
                }break;
            }
        }

    }

    return 0;
}

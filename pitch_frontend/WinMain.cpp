#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#   define NOMINMAX
#endif

#include <string>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include <projectY/gui/window.h>

#include <covid/socket.h>

void MsgBox(const char* title, const char* message)
{
    MessageBox(NULL, message, title, NULL);
}

INT WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR lpCmdLine,
    INT nCmdShow)
{
#if 0
    const auto socket = Socket::connectTo(Port("127.0.0.1", "49152"));
    socket.send({'t', 'e', 's', 't', '\0'});

    const auto messageInBytes = socket.receive();
    const auto message = std::string(messageInBytes.begin(), messageInBytes.end());
    MsgBox(message.c_str(), "received");
#endif

    auto window = gui::Window(gui::WindowRect(700, 400), "Pitch");

    while(window.isOpen())
    {
        window.update();
    }

    return 0;
}
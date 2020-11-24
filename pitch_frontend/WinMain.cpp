#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif

#include <string>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

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
    const auto socket = Socket::connectTo(Port("127.0.0.1", "49152"));
    socket.send({'t', 'e', 's', 't', '\0'});

    const auto messageInBytes = socket.receive();
    const auto message = std::string(messageInBytes.begin(), messageInBytes.end());
    MsgBox(message.c_str(), "received");

    return 0;
}
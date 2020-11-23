#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif

#include <string>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.WindowManagement.h>

void MsgBox(const char* title, const char* message)
{
    MessageBox(NULL, message, title, NULL);
}

void displayError(const char * msgStump)
{
    const auto error = WSAGetLastError();
    const auto msg = std::string(msgStump) + std::to_string(error);
    MsgBox("error", msg.c_str());
}

INT WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR lpCmdLine,
    INT nCmdShow)
{
    MsgBox("test window", "test window");

    //Init Winsock
    WSADATA wsaData;
    auto iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (iResult != 0) {
        MsgBox("Error", "WSAStartup failed: %d\n");
        return 1;
    }

    //Get IP Address info

    constexpr auto defaultPort = "49152";

    addrinfo* result = nullptr;
    addrinfo hints = {};

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the local address and port to be used by the server
    iResult = getaddrinfo("127.0.0.1", defaultPort, &hints, &result);
    if (iResult != 0) {
        MsgBox("error", "getaddrinfo failed");
        WSACleanup();
        return 1;
    }

    //initialize the socket and check for errors
    auto connectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (connectSocket == INVALID_SOCKET) {
        MsgBox("Error", "Could not initialize the socket");
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    int yes = 1;

    if (setsockopt(connectSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char *>(&yes), sizeof(int)) == -1) 
    {
        displayError("setsockopt failed because: ");
        freeaddrinfo(result);
        closesocket(connectSocket);
        WSACleanup();
        return 1;
    }

    // Connect to server.
    iResult = connect(connectSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        // Should really try the next address returned by getaddrinfo
        // if the connect call failed
        // But for this simple example we just free the resources
        // returned by getaddrinfo and print an error message

        displayError("connect failed because: ");
        closesocket(connectSocket);
        connectSocket = INVALID_SOCKET;
    }

    freeaddrinfo(result);

    if (connectSocket == INVALID_SOCKET) {
        displayError("connect is invalid: ");
        WSACleanup();
        return 1;
    }

    const auto bytesSent = send(connectSocket, "test", 5 * sizeof(char), 0);

    return 0;
}
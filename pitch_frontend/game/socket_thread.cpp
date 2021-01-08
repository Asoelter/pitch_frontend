#include "socket_thread.h"

#include <covid/socket.h>

#pragma message("This is a temporary include!!!")
#include <Windows.h>

SocketThread::SocketThread(const std::string& ipAddress, const std::string& portNumber)
    : thread_(socketMain, ipAddress, portNumber, std::ref(sendBuffer_), std::ref(receiveBuffer_))
{
}

SocketThread::~SocketThread()
{
    if(thread_.joinable())
    {
        thread_.join();
    }
}

bool SocketThread::hasMessageWaiting() noexcept
{
    return receiveBuffer_.topIfNotEmpty() == std::nullopt;
}

std::vector<char> SocketThread::message() noexcept
{
    const auto top = receiveBuffer_.popIfNotEmpty();
    return top.value_or(std::vector<char>());
}

void SocketThread::socketMain(std::string ipAddress,     std::string portNumber, 
                              MessageQueue& sendBuffer, MessageQueue& receiveBuffer)
{
    Socket socket = Socket::connectTo(Port(ipAddress, portNumber));

    while(true)
    {
        const auto possibleMessageToSend = sendBuffer.popIfNotEmpty();

        if(possibleMessageToSend)
        {
            socket.send(possibleMessageToSend.value());
        }

        const auto messageReceivedInBytes = socket.receive();
        const auto messageReceived = std::string(messageReceivedInBytes.begin(), messageReceivedInBytes.end());
        MessageBox(NULL, messageReceived.c_str(), messageReceived.c_str(), 0);
    }
}

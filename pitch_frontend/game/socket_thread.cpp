#include "socket_thread.h"

#pragma message("game/socket_thread.cpp(5): This is a temporary include!!!")
#include <Windows.h>

#include <covid/socket.h>

#include "message_decoder.h"


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

std::optional<Message> SocketThread::message() noexcept
{
    return receiveBuffer_.popIfNotEmpty();
}

void SocketThread::socketMain(std::string ipAddress,       std::string portNumber, 
                              RawMessageQueue& sendBuffer, MessageQueue& receiveBuffer)
{
    const auto socket = Socket::connectTo(Port(ipAddress, portNumber));
    MessageDecoder messageDecoder;

    while(true)
    {
        const auto possibleMessageToSend = sendBuffer.popIfNotEmpty();

        if(possibleMessageToSend)
        {
            socket.send(possibleMessageToSend.value());
        }

        if(socket.hasMessageWaiting())
        {
            const auto messageReceivedInBytes = socket.receive();
            messageDecoder.addMessageChunk(messageReceivedInBytes);
        }

        const auto mostRecentMessageReceived = messageDecoder.popMessage();

        if(mostRecentMessageReceived)
        {
            const auto message = mostRecentMessageReceived.value();
            const auto messageAsString = std::visit(MessageToString{}, message);
            //MessageBox(NULL, messageAsString.c_str(), "Message Received", NULL);
            receiveBuffer.push(message);
        }
    }
}

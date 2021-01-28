#ifndef SOCKET_THREAD_H
#define SOCKET_THREAD_H

#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <container/locked_message_queue.h>

#include "messages.h"

template<typename T>
concept MessageC = requires(T m)
{
    {m.serialize()} -> std::convertible_to<std::vector<char>>;
};

class SocketThread
{
public:
    using MessageType = std::vector<char>;

    SocketThread(const std::string& ipAddress, const std::string& portNumber);
    SocketThread(const SocketThread&) = delete;
    SocketThread(SocketThread&&) = delete;
    ~SocketThread();

    SocketThread& operator=(const SocketThread&) = delete;
    SocketThread& operator=(SocketThread&&) = delete;

    bool hasMessageWaiting() noexcept;
    std::optional<Message> message() noexcept;

    template<MessageC M>
    void sendMessage(const M& value)
    {
        sendBuffer_.push(value.serialize());
    }

private:
    using RawMessageQueue = LockedMessageQueue<MessageType>;
    using MessageQueue = LockedMessageQueue<Message>;

    static void socketMain(std::string ipAddress,        std::string portNumber, 
                           RawMessageQueue& sendBuffer,  MessageQueue& receiveBuffer);

private:
    RawMessageQueue sendBuffer_;
    MessageQueue receiveBuffer_;
    std::thread  thread_;
};

#endif //SOCKET_THREAD_H

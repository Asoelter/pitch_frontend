#ifndef SOCKET_THREAD_H
#define SOCKET_THREAD_H

#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <container/locked_message_queue.h>

template<typename T>
concept Message = requires(T m)
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
    std::vector<char> message() noexcept;

    template<Message M>
    void sendMessage(const M& value)
    {
        sendBuffer_.push(value.serialize());
    }

private:
    using MessageQueue = LockedMessageQueue<MessageType>;

    static void socketMain(std::string ipAddress,     std::string portNumber, 
                           MessageQueue& sendBuffer, MessageQueue& receiveBuffer);

private:
    LockedMessageQueue<MessageType> sendBuffer_;
    LockedMessageQueue<MessageType> receiveBuffer_;
    std::thread                     thread_;
};

#endif //SOCKET_THREAD_H

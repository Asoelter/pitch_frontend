#ifndef LOCKED_MESSAGE_QUEUE_H
#define LOCKED_MESSAGE_QUEUE_H

#include <mutex>
#include <optional>
#include <queue>

template<typename MessageType>
class LockedMessageQueue
{
public:
    LockedMessageQueue() = default;
    LockedMessageQueue(const LockedMessageQueue&) = delete;
    ~LockedMessageQueue() = default;

    LockedMessageQueue& operator=(const LockedMessageQueue&) = delete;
    LockedMessageQueue& operator=(LockedMessageQueue&&) = delete;

    std::optional<MessageType> popIfNotEmpty();
    std::optional<MessageType> topIfNotEmpty();
    void push(const MessageType& value);

private:
    std::queue<MessageType> queue_;
    std::mutex              mutex_;
};

#include "locked_message_queue.hpp"

#endif //LOCKED_MESSAGE_QUEUE_H

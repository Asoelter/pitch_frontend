template<typename MessageType>
std::optional<MessageType> LockedMessageQueue<MessageType>::popIfNotEmpty()
{
    std::lock_guard<std::mutex> lock(mutex_);

    if(queue_.empty())
    {
        return std::optional<MessageType>();
    }

    const auto topValue = queue_.front();
    queue_.pop();

    return std::optional<MessageType>(topValue);
}

template<typename MessageType>
std::optional<MessageType> LockedMessageQueue<MessageType>::topIfNotEmpty()
{
    std::lock_guard<std::mutex> lock(mutex_);

    if(queue_.empty())
    {
        return std::optional<MessageType>();
    }

    return std::optional<MessageType>(queue_.front());
}

template<typename MessageType>
void LockedMessageQueue<MessageType>::push(const MessageType& value)
{
    std::lock_guard<std::mutex> lock(mutex_);

    queue_.push(value);
}

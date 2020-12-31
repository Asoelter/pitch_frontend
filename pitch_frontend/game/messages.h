#ifndef MESSAGES_H
#define MESSAGES_H

#include "card.h"

namespace
{
    using StandardChunkType = uint16_t;
    constexpr size_t headerSize     = 2 * sizeof(StandardChunkType);
    constexpr size_t playerReadyId  = 1;
    constexpr size_t playedCardId   = 2;
}

struct PlayerReadyMessage
{
    std::vector<char> serialize() const;

    static constexpr StandardChunkType size = headerSize;
    static constexpr StandardChunkType type = playerReadyId;
};

struct PlayedCardMessage
{
    PlayedCardMessage(Card::Suit s, Card::Number n) : suit(s), number(n) {}

    std::vector<char> serialize() const;

    static constexpr StandardChunkType size = headerSize + sizeof(Card::Suit) + sizeof(Card::Number);
    static constexpr StandardChunkType type = playedCardId;

    Card::Suit   suit;
    Card::Number number;
};

#endif //MESSAGES_H

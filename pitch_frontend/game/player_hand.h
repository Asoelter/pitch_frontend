#ifndef PLAYER_HAND_H
#define PLAYER_HAND_H

#include <optional>
#include <vector>

#include "card.h"

class PlayerHand
{
public:
    PlayerHand() = default;

    void receive(CardSuit Suit, CardNumber number);
    bool play(CardSuit Suit, CardNumber number);
    size_t size() const noexcept;

private:
    std::vector<std::optional<Card>> cards_;
};

#endif //PLAYER_HAND_H

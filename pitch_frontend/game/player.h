#ifndef PLAYER_H
#define PLAYER_H

#include <optional>
#include <vector>

#include "card.h"

class Player
{
public:
    Player();

    bool play(CardSuit suit, CardNumber number);
    void receive(CardSuit suit, CardNumber number);

    uint8_t score() const noexcept;
    uint8_t pendingPoints() const noexcept;
    uint8_t gamePoints() const noexcept;
    uint8_t currentBid() const noexcept;
    void bid(uint8_t amount) noexcept;

private:
    using Hand = std::vector<std::optional<Card>>; 

    Hand    hand_;
    uint8_t score_;
    uint8_t pendingPoints_;
    uint8_t gamePoints_;
    uint8_t currentBid_;
};

#endif //PLAYER_H

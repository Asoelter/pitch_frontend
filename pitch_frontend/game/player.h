#ifndef PLAYER_H
#define PLAYER_H

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
    uint8_t bid() const noexcept;

private:
    //Hand hand_; //<Implement this
    uint8_t score_;
    uint8_t pendingPoints_;
    uint8_t gamePoints_;
    uint8_t currentBid_;
};

#endif //PLAYER_H

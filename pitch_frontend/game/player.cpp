#include "player.h"

#include <algorithm>

Player::Player()
    : hand_()
    , score_(0)
    , pendingPoints_(0)
    , gamePoints_(0)
    , currentBid_(0)
{
    
}

bool Player::play(CardSuit suit, CardNumber number)
{
    const auto isRightCard = [suit, number](const std::optional<Card>& card)
    {
        return card->is(suit, number);
    };
    
    auto it = std::remove_if(hand_.begin(), hand_.end(), isRightCard);
    const auto success = !(it == hand_.end());
    hand_.erase(it);

    return success;
}

void Player::receive(CardSuit suit, CardNumber number)
{
    hand_.emplace_back(std::in_place, suit, number);
}

uint8_t Player::score() const noexcept
{
    return score_;
}

uint8_t Player::pendingPoints() const noexcept
{
    return pendingPoints_;
}

uint8_t Player::gamePoints() const noexcept
{
    return gamePoints_;
}

uint8_t Player::currentBid() const noexcept
{
    return currentBid_;
}

void Player::bid(uint8_t amount) noexcept
{
    assert(currentBid_ == 0);
    currentBid_ = amount;
}

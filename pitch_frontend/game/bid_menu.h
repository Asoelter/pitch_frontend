#ifndef BID_MENU_H
#define BID_MENU_H

#include <optional>
#include <vector>

#include "card.h"

class BidMenu
{
public:
    BidMenu();

    void show();

    void setHand(const std::vector<std::optional<Card>>& hand);

    bool userHasSelected() const noexcept;

    CardSuit suit() const noexcept;
    CardNumber number() const noexcept;

private:
    struct CardInfo
    {
        CardInfo(CardSuit s, CardNumber n) : suit(s), number(n) {}

        CardSuit suit;
        CardNumber number;
    };

    std::vector<CardInfo> extractCardInfo(const std::vector<std::optional<Card>>& hand);

    std::vector<CardInfo> cards_;
    uint8_t selectedIndex_;
    bool userHasSelected_;
};

#endif //BID_MENU_H

#include "bid_menu.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

BidMenu::BidMenu()
    : cards_()
    , selectedIndex_(0)
    , userHasSelected_(false)
{
    
}

void BidMenu::show()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Bid menu");

    uint8_t index = 0;

    for(auto card : cards_)
    {
        const auto label = toString(card.number) + " of " + toString(card.suit);
        if(ImGui::Button(label.c_str()))
        {
            userHasSelected_ = true;
            selectedIndex_ = index;
        }

        if(index % 2 == 0)
        {
            ImGui::SameLine(100);
        }

        ++index;
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void BidMenu::setHand(const std::vector<std::optional<Card>>& hand)
{
    for(size_t i = 0; i < hand.size(); ++i)
    {
        if(hand[i])
        {
            const auto cardInfo = CardInfo(hand[i]->suit(), hand[i]->number());

            if(cards_.size() <= i)
            {
                cards_.push_back(cardInfo);
            }
            else
            {
                cards_[i] = cardInfo;
            }
        }
    }
}

bool BidMenu::userHasSelected() const noexcept
{
    return userHasSelected_;
}

CardSuit BidMenu::suit() const noexcept
{
    return cards_[selectedIndex_].suit;
}

CardNumber BidMenu::number() const noexcept
{
    return cards_[selectedIndex_].number;
}

std::vector<BidMenu::CardInfo> BidMenu::extractCardInfo(const std::vector<std::optional<Card>>& hand)
{
    std::vector<CardInfo> result;

    for(const auto& possibleCard : hand)
    {
        if(possibleCard)
        {
            result.emplace_back(possibleCard.value().suit(), possibleCard.value().number());
        }
    }

    return result;
}

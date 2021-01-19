#include "card.h"

#include <math/operations.h>

#include <util/resource_loader.h>

std::vector<float> createCardVertices();
std::string determineCardTexture(CardSuit suit, CardNumber number);
std::string determineCardTexture(Card::JokerType type);
std::string toString(CardSuit suit);
std::string toString(CardNumber number);

Card::Card(CardSuit suit, CardNumber number)
    : suit_(suit)
    , number_(number)
    , mesh_(VertexBufferObject(createCardVertices(), { 3, 2 }))
    , texture_(ResourceLoader::loadTexture(determineCardTexture(suit, number)))
    , position_(0.0f, 0.0f, 0.0f)
    , type_(NormalType{ suit, number })
{
    
}

Card::Card(JokerType jokerType)
    : mesh_(VertexBufferObject(createCardVertices(), { 3, 2 }))
    , texture_(ResourceLoader::loadTexture(determineCardTexture(jokerType)))
    , position_(0.0f, 0.0f, 0.0f)
    , type_(jokerType)
{
    assert(false && "This needs to be updated once jokers are integrated with card enums");
}

bool Card::is(CardSuit suit, CardNumber number) const noexcept
{
    return suit_ == suit && number_ == number;
}

void Card::translate(const Vec3& direction)
{
    mesh_.translate(direction);
    position_ = position_ + direction;
}

void Card::rotate(Radian radians)
{
    mesh_.rotate({ 0.0f, 0.0f, 1.0f }, radians);
}

void Card::rotate(Degree degrees)
{
    mesh_.rotate({ 0.0f, 0.0f, 1.0f }, degrees);
}

int8_t Card::normalPointValue() const noexcept
{
    const auto normalTypeInfo = std::get_if<NormalType>(&type_);

    if(!normalTypeInfo) //this card is a joker
    {
        return 1;
    }

    switch(normalTypeInfo->number)
    {
        case CardNumber::Jack:
        case CardNumber::Queen:
        case CardNumber::King:
        case CardNumber::Ace:
            return 1;
        default:
            return 0;
    }
}

int8_t Card::gamePointValue() const noexcept
{
    const auto normalTypeInfo = std::get_if<NormalType>(&type_);

    if(!normalTypeInfo) //this card is a joker
    {
        return 0;
    }

    switch(normalTypeInfo->number)
    {
        case CardNumber::Ten:   return 10;
        case CardNumber::Jack:  return 1;
        case CardNumber::Queen: return 2;
        case CardNumber::King:  return 3;
        case CardNumber::Ace:   return 4;
        default:            return 0;
    }
}

const Mesh& Card::mesh() const noexcept
{
    return mesh_;
}

void Card::prepareToRender() noexcept
{
    texture_.bind();
}

bool Card::isJoker() const
{
    static constexpr auto jokerIndex = 1;

    return type_.index() == jokerIndex;
}

std::vector<float> createCardVertices()
{
    
    return {
        -1.5f, -2.0f, 0.0f,  0.0f, 0.0f, //bottom left
         1.5f, -2.0f, 0.0f,  1.0f, 0.0f, //bottom right
        -1.5f,  2.0f, 0.0f,  0.0f, 1.0f, //top left

         1.5f, -2.0f, 0.0f,  1.0f, 0.0f, //bottom right
         1.5f,  2.0f, 0.0f,  1.0f, 1.0f, //top right
        -1.5f,  2.0f, 0.0f,  0.0f, 1.0f  //top left
    };
}

std::string determineCardTexture(CardSuit suit, CardNumber number)
{
    std::string suffix = ".png";

    if(number > CardNumber::Ten)
    {
        suffix = "2.png";
    }

    return toString(number) + "_of_" + toString(suit) + suffix;
}

std::string determineCardTexture(Card::JokerType type)
{
    if(type == Card::JokerType::High)
    {
        return "high_joker.png";
    }

    return "low_joker.png";
}

std::string toString(CardSuit suit)
{
    switch(suit)
    {
        case CardSuit::Heart:     return "hearts";
        case CardSuit::Club:      return "clubs";
        case CardSuit::Diamond:   return "diamonds";
        case CardSuit::Spade:     return "spade";
    }

    throw std::runtime_error("Unknown Suit");
}

std::string toString(CardNumber number)
{
    switch(number)
    {
        case CardNumber::Two:     return "2";
        case CardNumber::Three:   return "3";
        case CardNumber::Four:    return "4";
        case CardNumber::Five:    return "5";
        case CardNumber::Six:     return "6";
        case CardNumber::Seven:   return "7";
        case CardNumber::Eight:   return "8";
        case CardNumber::Nine:    return "9";
        case CardNumber::Ten:     return "10";
        case CardNumber::Jack:    return "jack";
        case CardNumber::Queen:   return "queen";
        case CardNumber::King:    return "king";
        case CardNumber::Ace:     return "ace";
    }

    throw std::runtime_error("Unknown card number");
}

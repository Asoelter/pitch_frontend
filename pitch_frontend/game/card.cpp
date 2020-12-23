#include "card.h"

#include <math/operations.h>

#include <util/resource_loader.h>

std::vector<float> createCardVertices();
std::string determineCardTexture(Card::Suit suit, Card::Number number);
std::string determineCardTexture(Card::JokerType type);
std::string toString(Card::Suit suit);
std::string toString(Card::Number number);

Card::Card(Suit suit, Number number)
    : mesh_(VertexBufferObject(createCardVertices(), { 3, 2 }))
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
        case Number::Jack:
        case Number::Queen:
        case Number::King:
        case Number::Ace:
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
        case Number::Ten:   return 10;
        case Number::Jack:  return 1;
        case Number::Queen: return 2;
        case Number::King:  return 3;
        case Number::Ace:   return 4;
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

std::string determineCardTexture(Card::Suit suit, Card::Number number)
{
    std::string suffix = ".png";

    if(number > Card::Number::Ten)
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

std::string toString(Card::Suit suit)
{
    switch(suit)
    {
        case Card::Suit::Heart:     return "hearts";
        case Card::Suit::Club:      return "clubs";
        case Card::Suit::Diamond:   return "diamonds";
        case Card::Suit::Spade:     return "spade";
    }

    throw std::runtime_error("Unknown Suit");
}

std::string toString(Card::Number number)
{
    switch(number)
    {
        case Card::Number::Two:     return "2";
        case Card::Number::Three:   return "3";
        case Card::Number::Four:    return "4";
        case Card::Number::Five:    return "5";
        case Card::Number::Six:     return "6";
        case Card::Number::Seven:   return "7";
        case Card::Number::Eight:   return "8";
        case Card::Number::Nine:    return "9";
        case Card::Number::Ten:     return "10";
        case Card::Number::Jack:    return "jack";
        case Card::Number::Queen:   return "queen";
        case Card::Number::King:    return "king";
        case Card::Number::Ace:     return "ace";
    }

    throw std::runtime_error("Unknown card number");
}

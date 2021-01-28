#include "card.h"

#include <math/operations.h>

#include <util/resource_loader.h>

std::vector<float> createCardVertices();
std::string determineCardTexture(CardSuit suit, CardNumber number);
std::string determineCardTexture(Card::JokerType type);

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

void Card::setPosition(const Point2D& newPosition)
{
    const auto newPosition3D = Point3D(newPosition.x(), newPosition.y(), 0.0f);
    const auto direction = newPosition3D - position_;

    translate(direction);
}

CardSuit Card::suit() const noexcept
{
    return suit_;
}

CardNumber Card::number() const noexcept
{
    return number_;
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
    constexpr auto halfWidth = Card::width / 2.0f;
    constexpr auto halfHeight= Card::height / 2.0f;

    return {
        -1.0f * halfWidth, -1.0f * halfHeight, 0.0f,  0.0f, 0.0f, //bottom left
         1.0f * halfWidth, -1.0f * halfHeight, 0.0f,  1.0f, 0.0f, //bottom right
        -1.0f * halfWidth,  1.0f * halfHeight, 0.0f,  0.0f, 1.0f, //top left

         1.0f * halfWidth, -1.0f * halfHeight, 0.0f,  1.0f, 0.0f, //bottom right
         1.0f * halfWidth,  1.0f * halfHeight, 0.0f,  1.0f, 1.0f, //top right
        -1.0f * halfWidth,  1.0f * halfHeight, 0.0f,  0.0f, 1.0f  //top left
    };
    
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

    if(number > CardNumber::Ten && number != CardNumber::Ace)
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

#ifndef CARD_H
#define CARD_H

#include <variant>

#include <graphics/mesh.h>
#include <graphics/texture.h>

class Card
{
public:
    enum class Suit
    {
        Heart,
        Club,
        Diamond,
        Spade
    };

    enum class Number
    {
        Two, Three, Four,  Five,
        Six, Seven, Eight, Nine,
        Ten, Jack,  Queen, King,
        Ace
    };

    enum class JokerType
    {
        High,
        Low
    };

    Card(Suit suit, Number number);
    Card(JokerType jokerType);

    void translate(const Vec3& direction);
    void rotate(Radian radians);
    void rotate(Degree degrees);

    static constexpr auto width  = 4.0f;
    static constexpr auto height = 4.0f;

private:
    Mesh    mesh_;
    Texture texture_;
};

#endif //CARD_H

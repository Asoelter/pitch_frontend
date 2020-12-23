#ifndef CARD_H
#define CARD_H

#include <variant>

#include <graphics/mesh.h>
#include <graphics/texture.h>

#include <math/point.h>

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

    int8_t normalPointValue() const noexcept;
    int8_t gamePointValue() const noexcept;

    const Mesh& mesh() const noexcept;

    void prepareToRender() noexcept;

    static constexpr auto width  = 3.0f;
    static constexpr auto height = 4.0f;

private:
    struct NormalType
    {
        Suit    suit;
        Number  number;
    };

    using Type = std::variant<NormalType, JokerType>;

    bool isJoker() const;

private:

    Mesh    mesh_;
    Texture texture_;
    Point3D position_;
    Type    type_;
};

#endif //CARD_H

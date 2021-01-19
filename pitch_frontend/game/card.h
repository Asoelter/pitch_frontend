#ifndef CARD_H
#define CARD_H

#include <variant>

#include <graphics/mesh.h>
#include <graphics/texture.h>

#include <math/point.h>

#include "card_enums.h"

class Card
{
public:
    //TODO(asoelter): refactor this into the Number and Suit enums
    enum class JokerType : unsigned char
    {
        High,
        Low
    };

    Card(CardSuit suit, CardNumber number);
    Card(JokerType jokerType);

    bool is(CardSuit suit, CardNumber number) const noexcept;

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
        CardSuit    suit;
        CardNumber  number;
    };

    using Type = std::variant<NormalType, JokerType>;

    bool isJoker() const;

private:
    CardSuit    suit_;
    CardNumber  number_;
    Mesh        mesh_;
    Texture     texture_;
    Point3D     position_;
    Type        type_;
};

#endif //CARD_H

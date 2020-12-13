#include "trig.h"

constexpr Radian::Radian(float value)
    : value_(value)
{
    
}

constexpr Radian Radian::operator+(Radian rhs) const
{
    return Radian(value_ + rhs.value_);
}

constexpr Radian& Radian::operator+=(Radian rhs)
{
    *this = *this + rhs;
    return *this;
}

constexpr Radian Radian::operator-(Radian rhs) const
{
    return Radian(value_ - rhs.value_);
}

constexpr Radian& Radian::operator-=(Radian rhs)
{
    *this = *this - rhs;
    return *this;
}

constexpr Radian Radian::operator*(Radian rhs) const
{
    return Radian(value_ * rhs.value_);
}

constexpr Radian& Radian::operator*=(Radian rhs)
{
    *this = *this / rhs;
    return *this;
}

constexpr Radian Radian::operator/(Radian rhs) const
{
    return Radian(value_ / rhs.value_);
}

constexpr Radian& Radian::operator/=(Radian rhs)
{
    *this = *this / rhs;
    return *this;
}

[[nodiscard]] float Radian::asFloat() const noexcept
{
    return value_;
}

Radian Radian::from(Degree degree)
{
    /*
     *
     *2pi rads = 360 degrees
     *
     *rads = (degree / 360) * 2pi
     *
     */

    return Radian((degree.asFloat() / 360.0f) * static_cast<float>(twoPi));
}

constexpr Degree::Degree(float value)
    : value_(value)
{
    
}

constexpr Degree Degree::operator+(Degree rhs)
{
    return Degree(value_ + rhs.value_);
}

constexpr Degree& Degree::operator+=(Degree rhs)
{
    *this = *this + rhs;
    return *this;
}

constexpr Degree Degree::operator-(Degree rhs)
{
    return Degree(value_ - rhs.value_);
    
}

constexpr Degree& Degree::operator-=(Degree rhs)
{
    
    *this = *this - rhs;
    return *this;
}

constexpr Degree Degree::operator*(Degree rhs)
{
    return Degree(value_ * rhs.value_);
    
}

constexpr Degree& Degree::operator*=(Degree rhs)
{
    
    *this = *this * rhs;
    return *this;
}

constexpr Degree Degree::operator/(Degree rhs)
{
    return Degree(value_ / rhs.value_);
}

constexpr Degree& Degree::operator/=(Degree rhs)
{
    *this = *this / rhs;
    return *this;
}

[[nodiscard]] constexpr float Degree::asFloat() const noexcept
{
    return value_;
}

Degree Degree::from(Radian radians)
{
    /*
     * 2pi rads = 360 degrees
     *
     * degrees = (radians / 2pi) * 360
     */

    return Degree((radians.asFloat() / static_cast<float>(twoPi)) * 360.0f);
}

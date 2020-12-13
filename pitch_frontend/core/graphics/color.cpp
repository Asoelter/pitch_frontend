#include "color.h"

#include <algorithm>

Color::Color(float red, float green, float blue, float alpha)
    : values_{red, green, blue, alpha}
{
    
}

Color::Color(const Color& rhs)
{
    std::copy(std::begin(rhs.values_), std::end(rhs.values_), std::begin(values_));
}


Color& Color::operator=(const Color& rhs)
{
    std::copy(std::begin(rhs.values_), std::end(rhs.values_), std::begin(values_));

    return *this;
}

float Color::r() const noexcept
{
    return values_[0];
}

float Color::g() const noexcept
{
    return values_[1];
}

float Color::b() const noexcept
{
    return values_[2];
}

float Color::a() const noexcept
{
    return values_[3];
}

Color Color::red(float alpha) noexcept
{
    return { 1.0f, 0.0f, 0.0f, alpha };
}

Color Color::green(float alpha) noexcept
{
    return { 0.0f, 1.0f, 0.0f, alpha };
}

Color Color::blue(float alpha) noexcept
{
    return { 0.0f, 0.0f, 1.0f, alpha };
}

Color Color::black(float alpha) noexcept
{
    return { 0.0f, 0.0f, 0.0f, alpha };
}

Color Color::white(float alpha) noexcept
{
    return { 1.0f, 1.0f, 1.0f, alpha };
}

Color Color::greyscale(float value, float alpha) noexcept
{
    return { value, value, value, alpha };
}

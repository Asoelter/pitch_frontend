#ifndef VEC_H
#define VEC_H

template<size_t Size>
class Vec
{
public:
    template<typename ... T>
    constexpr Vec(T ... values);

    constexpr Vec(const Vec<Size>& rhs);
    constexpr Vec(Vec<Size>&& rhs);

    constexpr Vec& operator=(const Vec<Size>& rhs);
    constexpr Vec& operator=(Vec<Size>&& rhs);

    constexpr Vec& operator+(const Vec<Size>& rhs);
    constexpr Vec& operator-(const Vec<Size>& rhs);

    constexpr float x() const noexcept;
    constexpr float y() const noexcept;
    constexpr float z() const noexcept;
    constexpr float w() const noexcept;

private:
    float data_[Size];
};

#include "vec.hpp"

#endif //VEC_H

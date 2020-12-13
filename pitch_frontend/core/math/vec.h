#ifndef VEC_H
#define VEC_H

template<size_t Size>
class Vec
{
public:
    constexpr Vec();

    template<typename ... T>
    constexpr Vec(T ... values);

    constexpr Vec(const Vec<Size>& rhs);
    constexpr Vec(Vec<Size>&& rhs);
    ~Vec() = default;

    constexpr Vec& operator=(const Vec<Size>& rhs);
    constexpr Vec& operator=(Vec<Size>&& rhs) noexcept;

    constexpr Vec& operator+=(const Vec<Size>& rhs);
    constexpr Vec& operator-=(const Vec<Size>& rhs);

    [[nodiscard]] constexpr Vec operator+(const Vec<Size>& rhs);
    [[nodiscard]] constexpr Vec operator-(const Vec<Size>& rhs);

    [[nodiscard]] constexpr float x() const noexcept;
    [[nodiscard]] constexpr float y() const noexcept;
    [[nodiscard]] constexpr float z() const noexcept;
    [[nodiscard]] constexpr float w() const noexcept;

    [[nodiscard]] constexpr float operator[](size_t index) const; 
    constexpr float& operator[](size_t index);

    [[nodiscard]] constexpr const float* data() const noexcept;

private:
    float data_[Size];
};

template<size_t Size>
float dot(const Vec<Size>& lhs, const Vec<Size>& rhs);

#include "vec.hpp"

using Vec2 = Vec<2>;
using Vec3 = Vec<3>;
using Vec4 = Vec<4>;

using Axis = Vec3;

//static const Axis xAxis = Vec3(1.0f, 0.0f, 0.0f);
//static const Axis yAxis = Vec3(0.0f, 1.0f, 0.0f);
//static const Axis zAxis = Vec3(0.0f, 0.0f, 1.0f);

#endif //VEC_H

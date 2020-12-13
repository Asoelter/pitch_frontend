#include <type_traits>

#include <cassert>
#include <numeric>

#include "../container/typelist.h"

template<size_t Size >
constexpr Vec<Size>::Vec()
    : data_{}
{
    for(size_t i = 0; i < Size; ++i)
    {
        data_[i] = 0.0f;
    }
}

template<size_t Size >
template<typename ... T>
constexpr Vec<Size>::Vec(T ... values)
{
    static_assert(IsAll<float, Typelist<T...>>);
    static_assert(sizeof...(T) == Size, "Invalid number of parameters");

    int index = 0;

    for(const auto value : {values...})
    {
        data_[index] = value;
        ++index;
    }
}

template<size_t Size >
constexpr Vec<Size>::Vec(const Vec<Size>& rhs)
{
    *this = rhs;
}

template<size_t Size >
constexpr Vec<Size>::Vec(Vec<Size>&& rhs)
{
    *this = rhs;
}

template<size_t Size >
constexpr Vec<Size>& Vec<Size>::operator=(const Vec<Size>& rhs)
{
    std::copy(std::begin(rhs.data_), std::end(rhs.data_), std::begin(data_));

    return *this;
}

template<size_t Size >
constexpr Vec<Size>& Vec<Size>::operator=(Vec<Size>&& rhs) noexcept
{
    std::copy(std::begin(rhs.data_), std::end(rhs.data_), std::begin(data_));

    return *this;
}

template<size_t Size >
constexpr Vec<Size>& Vec<Size>::operator+=(const Vec<Size>& rhs)
{
    *this = *this + rhs;
    return *this;
}

template<size_t Size >
constexpr Vec<Size>& Vec<Size>::operator-=(const Vec<Size>& rhs)
{
    *this = *this - rhs;
    return *this;
}

template<size_t Size >
[[nodiscard]] constexpr Vec<Size> Vec<Size>::operator+(const Vec<Size>& rhs)
{
    Vec<Size> result;

    for(size_t i = 0; i < Size; ++i)
    {
        result.data_[i] = data_[i] + rhs.data_[i];
    }

    return result;
}

template<size_t Size >
[[nodiscard]] constexpr Vec<Size> Vec<Size>::operator-(const Vec<Size>& rhs)
{
    Vec<Size> result;

    for(int i = 0; i < Size; ++i)
    {
        result.data_[i] = data_[i] - rhs.data_[i];
    }

    return result;
}

template<size_t Size >
[[nodiscard]] constexpr float Vec<Size>::x() const noexcept
{
    static_assert(Size > 0, "no x element in vector of this size");
    return data_[0];
}

template<size_t Size >
[[nodiscard]] constexpr float Vec<Size>::y() const noexcept
{
    static_assert(Size > 1, "no y element in vector of this size");
    return data_[1];
}

template<size_t Size >
[[nodiscard]] constexpr float Vec<Size>::z() const noexcept
{
    static_assert(Size > 2, "no z element in vector of this size");
    return data_[2];
}

template<size_t Size >
[[nodiscard]] constexpr float Vec<Size>::w() const noexcept
{
    static_assert(Size > 3, "no w element in vector of this size");
    return data_[3];
}

template<size_t Size >
[[nodiscard]] constexpr float Vec<Size>::operator[](size_t index) const
{
    assert(index < Size && "Out of bounds access");
    return data_[index];
}

template<size_t Size >
constexpr float& Vec<Size>::operator[](size_t index)
{
    assert(index < Size && "Out of bounds access");
    return data_[index];
}

template<size_t Size>
float dot(const Vec<Size>& lhs, const Vec<Size>& rhs)
{
    float result = 0.0f;

    for(size_t i = 0; i < Size; ++i)
    {
        result += (lhs[i] + rhs[i]);
    }

    return result;
}

template<size_t Size>
[[nodiscard]] constexpr const float* Vec<Size>::data() const noexcept
{
    return &data_[0];
}

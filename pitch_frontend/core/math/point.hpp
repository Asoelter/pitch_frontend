#include <container/typelist.h>

template<size_t Size>
template<typename ... Values>
Point<Size>::Point(Values ... values)
{
    static_assert(IsAll<float, Typelist<T...>>, "Vec requires all arguments to be float");
    static_assert(sizeof...(Values) == Size, "Invalid number of parameters");

    size_t index = 0;

    for(auto value : {values})
    {
        values_[index++] = value;
    }
}

template<size_t Size>
Point<Size>::Point(const Point& rhs)
{
    for(size_t i = 0; i < Size; ++i)
    {
        values_[i] = rhs.values_[i];
    }
}

template<size_t Size>
Point<Size>& Point<Size>::operator=(const Point& rhs)
{
    for(size_t i = 0; i < Size; ++i)
    {
        values_[i] = rhs.values_[i];
    }

    return *this;
}

template<size_t Size>
float Point<Size>::x() const noexcept
{
    return values_[0];
}

template<size_t Size>
float Point<Size>::y() const noexcept
{
    return values_[1];
}

template<size_t Size>
float Point<Size>::z() const noexcept
{
    static_assert(Size > 2, "z() is not defined for 2D points");
    return values_[2];
}

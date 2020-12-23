#ifndef POINT_H
#define POINT_H

template<size_t Size>
class Point
{
public:
    Point();
    template<typename ... Values>
    Point(Values ... values);

    Point(const Point& rhs);
    ~Point() = default;

    Point& operator=(const Point& rhs);

    float x() const noexcept;
    float y() const noexcept;
    float z() const noexcept;

    float operator[](size_t index) const noexcept(!DEBUG);
    float& operator[](size_t index) noexcept(!DEBUG);

private:
    float values_[Size];
};

using Point2D = Point<2>;
using Point3D = Point<3>;

#include "point.hpp"

#undef IS_DEBUG_MODE

#endif //POINT_H

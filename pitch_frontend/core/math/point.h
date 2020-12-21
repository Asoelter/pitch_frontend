#ifndef POINT_H
#define POINT_H

#include <type_traits>

template<size_t Size>
class Point
{
public:
    template<typename ... Values>
    Point(Values ... values);

    Point(const Point& rhs);
    ~Point() = default;

    Point& operator=(const Point& rhs);

    float x() const noexcept;
    float y() const noexcept;
    float z() const noexcept;

private:
    float values_[Size];
};

using Point2D = Point<2>;
using Point3D = Point<3>;

#include "point.hpp"

#endif //POINT_H

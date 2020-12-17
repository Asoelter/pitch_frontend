#include "vec.h"

Vec<3> cross(const Vec<3>& lhs, const Vec<3>& rhs)
{
    /*
     * Formula:
     *
     * __          __
     * |  i  j  k   |
     * |  x1 y1 z1  | = (y1z2 - y2z1)i - (x1z2 - x2z1)j + (x1y2 - x2y1)k
     * |_ x2 y2 z2 _|
     */

    const auto y1z2 = lhs.y() * rhs.z();
    const auto y2z1 = rhs.y() * lhs.z();
    const auto x1z2 = lhs.x() * rhs.z();
    const auto x2z1 = rhs.x() * lhs.z();
    const auto x1y2 = lhs.x() * rhs.y();
    const auto x2y1 = rhs.x() * lhs.y();

    const auto i = y1z2 - y2z1;
    const auto j = x2z1 - x1z2;
    const auto k = x1y2 - x2y1;

    return { i, j, k };
}

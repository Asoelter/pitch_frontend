#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "vec.h"
#include "point.h"

template<size_t Size>
Point<Size> operator+(const Point<Size>& p, const Vec<Size>& v);

template<size_t Size>
Point<Size> operator+(const Vec<Size>& v, const Point<Size>& p);

#include "operations.hpp"

#endif //OPERATIONS_H

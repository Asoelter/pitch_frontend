#ifndef MAT_H
#define MAT_H

#include "vec.h"

template<size_t N, size_t M>
class Mat
{
public:
    constexpr Mat();
    constexpr Mat(const Mat& rhs);
    constexpr Mat(Mat&& rhs);
    ~Mat() = default;

    constexpr Mat& operator=(const Mat& rhs);
    constexpr Mat& operator=(Mat&& rhs);

    constexpr Mat operator+(const Mat& rhs);
    constexpr Mat& operator+=(const Mat& rhs);
    
    constexpr Mat operator*(const Mat& rhs);
    constexpr Mat& operator*=(const Mat& rhs);

    static constexpr Mat identity();
    static constexpr Mat translate(const Vec<N>& displacement);
    static constexpr Mat rotate();

private:
    float data_[N][M];
};

#include "mat.hpp"

using Mat2 = Mat<2, 2>;
using Mat3 = Mat<3, 3>;
using Mat4 = Mat<4, 4>;

#endif //MAT_H

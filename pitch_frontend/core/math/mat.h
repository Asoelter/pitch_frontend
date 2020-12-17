#ifndef MAT_H
#define MAT_H

#include "trig.h"
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

    [[nodiscard]] constexpr Mat operator+(const Mat& rhs);
    constexpr Mat& operator+=(const Mat& rhs);
    
    [[nodiscard]] constexpr Mat operator*(const Mat& rhs);
    constexpr Mat& operator*=(const Mat& rhs);

    [[nodiscard]] constexpr const float* data() const noexcept;

    [[nodiscard]] static constexpr Mat identity();
    [[nodiscard]] static constexpr Mat translate(const Vec<N>& displacement);
    [[nodiscard]] static constexpr Mat rotate(const Vec<N>& axis, Radian angle);
    [[nodiscard]] static constexpr Mat rotate(const Vec<N>& axis, Degree angle);
    [[nodiscard]] static constexpr Mat<4, 4> lookAt(const Vec<3>& eye, const Vec<3>& center, const Vec<3>& up);

private:
    float data_[N][M];
};

using Mat2 = Mat<2, 2>;
using Mat3 = Mat<3, 3>;
using Mat4 = Mat<4, 4>;

#include "mat.hpp"

#endif //MAT_H

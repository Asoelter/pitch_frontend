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
    constexpr Mat& operator=(Mat&& rhs) noexcept;

    [[nodiscard]] constexpr Mat operator+(const Mat& rhs) const;
    constexpr Mat& operator+=(const Mat& rhs);
    
    [[nodiscard]] constexpr Mat operator*(const Mat& rhs) const;
    constexpr Mat& operator*=(const Mat& rhs);

    [[nodiscard]] constexpr const float* data() const noexcept;

    [[nodiscard]] constexpr const Vec<M>& operator[](size_t index) const;
    [[nodiscard]] constexpr Vec<M>& operator[](size_t index) ;

    [[nodiscard]] static constexpr Mat identity();
    [[nodiscard]] static constexpr Mat<4, 4> translate(const Vec<3>& displacement);
    [[nodiscard]] static constexpr Mat<4, 4> rotate(const Vec<3>& axis, Radian angle);
    [[nodiscard]] static constexpr Mat<4, 4> rotate(const Vec<3>& axis, Degree angle);
    [[nodiscard]] static constexpr Mat<4, 4> lookAt(const Vec<3>& eye, const Vec<3>& center, const Vec<3>& up);
    [[nodiscard]] static constexpr Mat<4, 4> orthographic(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);

private:
    union
    {
        float data_[N][M];
        Vec<N> vecs_[M];
    };
};

using Mat2 = Mat<2, 2>;
using Mat3 = Mat<3, 3>;
using Mat4 = Mat<4, 4>;

#include "mat.hpp"

#endif //MAT_H

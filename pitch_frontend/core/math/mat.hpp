#include <cmath>

template<size_t N, size_t M>
constexpr Mat<N, M>::Mat()
    : data_()
{
    memset(data_, 0, N + M);
}

template<size_t N, size_t M>
constexpr Mat<N, M>::Mat(const Mat& rhs)
{
    for(size_t j = 0; j < M; ++j)
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[j][i] = rhs.data_[j][i];
        }
    }
}

template<size_t N, size_t M>
constexpr Mat<N, M>::Mat(Mat&& rhs)
{
    for(size_t j = 0; j < M; ++j)
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[j][i] = rhs.data_[j][i];
        }
    }
}

template<size_t N, size_t M>
constexpr Mat<N, M>& Mat<N, M>::operator=(const Mat& rhs)
{
    for(size_t j = 0; j < M; ++j)
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[j][i] = rhs.data_[j][i];
        }
    }

    return *this;
}

template<size_t N, size_t M>
constexpr Mat<N, M>& Mat<N, M>::operator=(Mat&& rhs) noexcept
{
    for(size_t j = 0; j < M; ++j)
    {
        for(size_t i = 0; i < N; ++i)
        {
            data_[j][i] = rhs.data_[j][i];
        }
    }

    return *this;
}

template<size_t N, size_t M>
constexpr Mat<N, M> Mat<N, M>::operator+(const Mat& rhs) const
{
    Mat<N, M> result;

    for(size_t j = 0; j < M; ++j)
    {
        for(size_t i = 0; i < N; ++i)
        {
            result.data_[j][i] = data_[j][i] + rhs.data_[j][i];
        }
    }

    return result;
}

template<size_t N, size_t M>
constexpr Mat<N, M>& Mat<N, M>::operator+=(const Mat& rhs)
{
    *this = *this + rhs;
    return *this;
}

template<size_t N, size_t M>
constexpr Mat<N, M> Mat<N, M>::operator*(const Mat& rhs) const
{
    Mat<N, M> result;

    for(size_t j = 0; j < M; ++j)
    {
        for(size_t i = 0; i < N; ++i)
        {
            result.data_[i][j] = 0;

            for(size_t k = 0; k < N; ++k)
            {
                result.data_[i][j] += data_[i][k] * rhs.data_[k][j];
            }
        }
    }

    return result;
}

template<size_t N, size_t M>
constexpr Mat<N, M>& Mat<N, M>::operator*=(const Mat& rhs)
{
    *this = *this * rhs;
    return *this;
}

template<size_t N, size_t M>
constexpr const float* Mat<N, M>::data() const noexcept
{
    return &data_[0][0];
}

template<size_t N, size_t M>
[[nodiscard]] constexpr const Vec<M>& Mat<N, M>::operator[](size_t index) const
{
    return vecs_[index];
}

template<size_t N, size_t M>
[[nodiscard]] constexpr Vec<M>& Mat<N, M>::operator[](size_t index)
{
    return vecs_[index];
}

template<size_t N, size_t M>
constexpr Mat<N, M> Mat<N, M>::identity()
{
    Mat<N, M> result;
    
    for (size_t j = 0; j < M; ++j)
    {
        for (size_t i = 0; i < N; ++i)
        {
            result[j][i] = static_cast<float>(i == j);
        }
    }

    return result;
}

template<size_t N, size_t M>
constexpr Mat<4, 4> Mat<N, M>::translate(const Vec<3>& displacement)
{
    auto result = Mat4::identity();

    result[3][0] = displacement.x();
    result[3][1] = displacement.y();
    result[3][2] = displacement.z();

    return result;
}

template<size_t N, size_t M>
[[nodiscard]] constexpr Mat<4, 4> Mat<N, M>::rotate(const Vec<3>& axis, Radian angle)
{
    /*
     * Formula:
     *
     * __                                                  __
     * |  (1-c)x^2 + c    (1-c)xy - sz    (1-c)xz + sy    0 |
     * |  (1-c)xy + sz    (1-c)y^2 + c    (1-c)yz - sz    0 |
     * |  (1-c)xz - sy    (1-c)yz + sz    (1-c)z^2 + c    0 |
     * |_      0               0               0          1_|
     *
     * Where: c = cos(theta), s = sin(theta)
     */
    
    static_assert(N == 4, "rotation matrices are only defined for four dimensions");

    const auto c = std::cos(angle.asFloat());
    const auto s = std::sin(angle.asFloat());
    const auto oneMinusC = 1.0f - c;

    const auto x = axis.x();
    const auto y = axis.y();
    const auto z = axis.z();

    Mat<N, M> result;

    result.data_[0][0] = (oneMinusC * (x * x)) + c;
    result.data_[0][1] = (oneMinusC * (x * y)) - (s * z);
    result.data_[0][2] = (oneMinusC * (x * z)) + (s * y);
    result.data_[0][3] = 0.0f;

    result.data_[1][0] = (oneMinusC * (x * y)) + (s * z);
    result.data_[1][1] = (oneMinusC * (y * y)) + c;
    result.data_[1][2] = (oneMinusC * (y * z)) - (s * z);
    result.data_[1][3] = 0.0f;

    result.data_[2][0] = (oneMinusC * (x * z)) - (s * y);
    result.data_[2][1] = (oneMinusC * (y * z)) + (s * z);
    result.data_[2][2] = (oneMinusC * (z * z)) + c;
    result.data_[2][3] = 0.0f;

    result.data_[3][0] = 0.0f;
    result.data_[3][1] = 0.0f;
    result.data_[3][2] = 0.0f;
    result.data_[3][3] = 1.0f;

    return result;
}

template<size_t N, size_t M>
[[nodiscard]] constexpr Mat<4, 4> Mat<N, M>::rotate(const Vec<3>& axis, Degree angle)
{
    return rotate(axis, Radian::from(angle));
}

template<size_t N, size_t M>
[[nodiscard]] constexpr Mat<4, 4> Mat<N, M>::lookAt(const Vec<3>& eye, const Vec<3>& center, const Vec<3>& up)
{
    const auto forward = normalize(eye - center);
    const auto right = normalize(cross(normalize(up), forward));

    Mat4 lhs = Mat4::identity();

    lhs[0][0] = right.x();
    lhs[0][1] = right.y();
    lhs[0][2] = right.z();

    lhs[1][0] = up.x();
    lhs[1][1] = up.y();
    lhs[1][2] = up.z();

    lhs[2][0] = forward.x();
    lhs[2][1] = forward.y();
    lhs[2][2] = forward.z();

    Mat4 rhs = Mat4::identity();

    rhs[3][0] = -1.0f * eye.x();
    rhs[3][1] = -1.0f * eye.y();
    rhs[3][2] = -1.0f * eye.z();

    return rhs * lhs;
}

template<size_t N, size_t M>
[[nodiscard]] constexpr Mat<4, 4> Mat<N, M>::orthographic(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
{
    /*                                                                      
     * Formula:                                                             
     *                                                                      
     * __                                                                 __
     * | 2 / (r - l)         0                0         -(r + l) / (r - l) |
     * |     0          2 / (t - b)           0         -(t + b) / (t - b) |
     * |     0               0          -2 / (f - n)    -(f + n) / (f - n) |
     * |_    0               0                0                  1        _|
     *
     * Where l = left   (xmin)
     *       r = right  (xmax)
     *       b = bottom (ymin)
     *       t = top    (ymax)
     *       n = near   (zmin)
     *       f = far    (zmax)
     */

    const auto diagonalValue = [](float min, float max) {return 2.0f / (max - min); };
    const auto columnValue = [](float min, float max) {return -1.0f * ((max + min) / (max - min)); };

    Mat4 result;

    result[0][0] = diagonalValue(xmin, xmax);
    result[1][1] = diagonalValue(ymin, ymax);
    result[2][2] = -1.0f * diagonalValue(zmin, zmax);
    result[3][3] = 1.0f;

    result[3][0] = columnValue(xmin, xmax);
    result[3][1] = columnValue(ymin, ymax);
    result[3][2] = columnValue(zmin, zmax);

    return result;
}

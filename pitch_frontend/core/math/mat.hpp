#include <cmath>

template<size_t N, size_t M>
constexpr Mat<N, M>::Mat()
    : data_()
{
    
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
}

template<size_t N, size_t M>
constexpr Mat<N, M>& Mat<N, M>::operator=(Mat&& rhs)
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
constexpr Mat<N, M> Mat<N, M>::operator+(const Mat& rhs)
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
constexpr Mat<N, M> Mat<N, M>::operator*(const Mat& rhs)
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
constexpr Mat<N, M> Mat<N, M>::identity()
{
    Mat<N, M> result;
    
    for (size_t j = 0; j < M; ++j)
    {
        for (size_t i = 0; i < N; ++i)
        {
            result.data_[j][i] = static_cast<float>(i == j);
        }
    }

    return result;
}

template<size_t N, size_t M>
constexpr Mat<N, M> Mat<N, M>::translate(const Vec<N>& displacement)
{
    auto result = identity();

    for(int i = 0; i < N; ++i)
    {
        result.data_[M - 1][i] = displacement[i];
    }

    return result;
}

template<size_t N, size_t M>
[[nodiscard]] constexpr Mat<N, M> Mat<N, M>::rotate(const Vec<N>& axis, Radian angle)
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
[[nodiscard]] constexpr Mat<N, M> Mat<N, M>::rotate(const Vec<N>& axis, Degree angle)
{
    return rotate(axis, Radian::from(angle));
}

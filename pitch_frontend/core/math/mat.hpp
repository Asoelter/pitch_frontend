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
        result.data_[M][i] = displacement[i];
    }

    return result;
}

template<size_t N, size_t M>
constexpr Mat<N, M> Mat<N, M>::rotate()
{
    
}

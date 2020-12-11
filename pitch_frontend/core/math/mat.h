#ifndef MAT_H
#define MAT_H

template<size_t N, size_t M>
class Mat
{
public:
    constexpr Mat();
    constexpr Mat(const Mat& rhs);
    constexpr Mat(Mat&& rhs);
    ~Mat() = default;

    constexpr Mat identity() const;
    constexpr Mat translate() const;
    constexpr Mat rotate() const;

private:
    float data_[N][M];
};

using Mat2 = Mat<2, 2>;
using Mat3 = Mat<3, 3>;
using Mat4 = Mat<4, 4>;

#endif //MAT_H

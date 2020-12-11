#ifndef MAT_H
#define MAT_H

template<size_t N, size_t M>
class Mat
{
public:

private:
    float data_[N][M];
};

using Mat2 = Mat<2, 2>;
using Mat3 = Mat<3, 3>;
using Mat4 = Mat<4, 4>;

#endif //MAT_H

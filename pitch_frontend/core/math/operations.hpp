template<size_t Size>
Point<Size> operator+(const Point<Size>& p, const Vec<Size>& v)
{
    Point<Size> result;

    for(int i = 0; i < Size; ++i)
    {
        result[i] = p[i] + v[i];
    }

    return result;
}

template<size_t Size>
Point<Size> operator+(const Vec<Size>& v, const Point<Size>& p)
{
    return p + v;
}

template<size_t Size>
Vec<Size> operator-(const Point<Size>& lhs, const Point<Size>& rhs)
{
    Vec<Size> result;

    for(size_t i = 0; i < Size; ++i)
    {
        result[i] = lhs[i] - rhs[i];
    }

    return result;
}

template<typename ... Args>
struct VarargsToFloatArray
{
    float values[sizeof...(Args)];
};

template<size_t Size >
template<typename ... T>
constexpr Vec<Size>::Vec(T ... values)
{
    
}

template<size_t Size >
constexpr Vec<Size>::Vec(const Vec<Size>& rhs)
{
    
}

template<size_t Size >
constexpr Vec<Size>::Vec(Vec<Size>&& rhs)
{
    
}

template<size_t Size >
constexpr Vec<Size>::Vec& operator=(const Vec<Size>& rhs)
{
    
}

template<size_t Size >
constexpr Vec<Size>::Vec& operator=(Vec<Size>&& rhs)
{
    
}

template<size_t Size >
constexpr Vec<Size>::Vec& operator+(const Vec<Size>& rhs)
{
    
}

template<size_t Size >
constexpr Vec<Size>::Vec& operator-(const Vec<Size>& rhs)
{
    
}

template<size_t Size >
constexpr float Vec<Size>::x() const noexcept
{
    
}

template<size_t Size >
constexpr float Vec<Size>::y() const noexcept
{
    
}

template<size_t Size >
constexpr float Vec<Size>::z() const noexcept
{
    
}

template<size_t Size >
constexpr float Vec<Size>::w() const noexcept
{
    
}

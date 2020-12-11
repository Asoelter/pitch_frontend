#ifndef TYPELIST_H
#define TYPELIST_H

template<typename ... Args>
struct Typelist
{
    
};

//-------------------Head----------------------

template<typename T>
struct HeadT;

template<typename T, typename ... Args>
struct HeadT<Typelist<T, Args...>>
{
    using type = T;
};

template<typename T>
using Head = typename HeadT<T>::type;

//-------------------Tail----------------------

template<typename T>
struct TailT;

template<typename T, typename ... Args>
struct TailT<Typelist<T, Args...>>
{
    using type = Typelist<Args...>;
};

template<typename T>
using Tail = typename TailT<T>::type;

//-------------------IsAll----------------------
template<typename T, typename ... Args>
struct IsAllT;

template<typename T, typename ... Args>
struct IsAllT<T, Typelist<Args...>>
{
    static constexpr bool value = std::is_same_v<T, Head<Typelist<Args...>>> && IsAllT<T, Tail<Typelist<Args...>>>::value;
};

template<typename T, typename V>
struct IsAllT<T, Typelist<V>>
{
    static constexpr bool value = std::is_same_v<T, V>;
};

template<typename T, typename ... Args>
constexpr bool IsAll = IsAllT<T, Args...>::value;

//-------------------IsHomogenous----------------------
template<typename T>
struct IsHomogenousT;

template<typename ... Args>
struct IsHomogenousT<Typelist<Args...>>
{
    using type = Head<Typelist<Args...>>;
    static constexpr bool value = IsAll < type, Typelist<Tail<Args...>>>;
};

template<typename T>
constexpr bool IsHomogenous = IsHomogenousT<T>::value;

#endif //TYPELIST_H

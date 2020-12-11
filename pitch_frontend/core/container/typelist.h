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
struct TailT
{
    using type = Typelist<Args...>;
};

template<typename T>
using Tail = typename Tail<T>::type;

#endif //TYPELIST_H

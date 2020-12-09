#ifndef ALGORITHM_H
#define ALGORITHM_H

template<typename InputIterator, typename ElementType>
InputIterator findLast(InputIterator begin, InputIterator end, const ElementType& value)
{
    auto walker = end; //copy end so we can return it to indicate nothing is found
    while(walker >= begin)
    {
        --walker;

        if(*walker == value)
        {
            return walker;
        }
    }

    return end;
}

#endif //ALGORITHM_H

/*******************************************
 * Author:      Adam Soelter               *
 * Date:        12/7/2020                  *
 * Description: 
 *******************************************/

#ifndef VERTEX_BUFFER_OBJECT
#define VERTEX_BUFFER_OBJECT

#include <array>
#include <vector>

#include <limits>

class VertexBufferObject
{
public:
    VertexBufferObject(const std::vector<float>& values, const std::vector<unsigned>& valuesPerIndex);

    void bind() noexcept;
    void unbind() noexcept;

private:
    static constexpr auto none = std::numeric_limits<unsigned>::max();
    static unsigned currentlyBoundId;
    unsigned id_;
};

#endif //VERTEX_BUFFER_OBJECT

/*******************************************
 * Author:      Adam Soelter               *
 * Date:        12/7/2020                  *
 * Description: 
 *******************************************/

#ifndef VERTEX_BUFFER_OBJECT
#define VERTEX_BUFFER_OBJECT

#include <vector>

class VertexBufferObject
{
public:
    VertexBufferObject(const std::vector<float>& values, const std::vector<unsigned>& valuesPerVertex);

    void bind() noexcept;
    void unbind() noexcept;

    size_t vertexCount() const noexcept;

private:
    unsigned id_;
    size_t vertexCount_;
};

#endif //VERTEX_BUFFER_OBJECT

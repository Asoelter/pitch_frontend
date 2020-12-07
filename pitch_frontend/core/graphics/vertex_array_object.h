#ifndef VERTEX_ARRAY_OBJECT_H
#define VERTEX_ARRAY_OBJECT_H

#include <limits>

class VertexArrayObject
{
public:
    VertexArrayObject();
    VertexArrayObject(const VertexArrayObject&) = delete;
    VertexArrayObject(VertexArrayObject&&) noexcept = default;
    ~VertexArrayObject();

    VertexArrayObject& operator=(const VertexArrayObject&) = delete;
    VertexArrayObject& operator=(VertexArrayObject&&) noexcept = default;

    void bind();
    void unbind();

    static bool boundVaoExists() noexcept;

private:
    static constexpr unsigned int noVaoIsBound_ = std::numeric_limits<unsigned int>::max();
    static unsigned int currentlyBoundVao_;
    unsigned int vao_;
};

#endif //VERTEX_ARRAY_OBJECT_H

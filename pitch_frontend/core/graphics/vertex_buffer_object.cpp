#include "vertex_buffer_object.h"

#include <glad/glad.h>

#include <numeric>

VertexBufferObject::VertexBufferObject(const std::vector<float>& values, const std::vector<unsigned>& valuesPerVertex)
    : id_(0)
{
    glGenBuffers(1, &id_);
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferData(GL_ARRAY_BUFFER, values.size() * sizeof(float), values.data(), GL_STATIC_DRAW);

    const auto valuesPerIndex = std::accumulate(valuesPerVertex.begin(), valuesPerVertex.end(), 0u);
    vertexCount_ = values.size() / valuesPerIndex;

    for(size_t i = 0; i < valuesPerVertex.size(); ++i)
    {
        const auto valuesBeforeThisAttribute = std::accumulate(&valuesPerVertex[0], &valuesPerVertex[i], 0u);

        glVertexAttribPointer(static_cast<GLuint>(i), 
                              valuesPerVertex[i], 
                              GL_FLOAT, 
                              GL_FALSE, 
                              valuesPerIndex * sizeof(float), 
                              reinterpret_cast<void*>(valuesBeforeThisAttribute * sizeof(float)));

        glEnableVertexAttribArray(static_cast<GLuint>(i));
    }
}

void VertexBufferObject::bind() noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void VertexBufferObject::unbind() noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

size_t VertexBufferObject::vertexCount() const noexcept
{
    return vertexCount_;
}

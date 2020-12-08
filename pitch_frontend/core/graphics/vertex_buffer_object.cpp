#include "vertex_buffer_object.h"

#include <glad/glad.h>

#include <numeric>

unsigned VertexBufferObject::currentlyBoundId = none;

VertexBufferObject::VertexBufferObject(const std::vector<float>& values, const std::vector<unsigned>& valuesPerAttribute)
    : id_(none)
{
#pragma message("NOTE: If you get odd stuff, check if sending too much data is the problem")
    glGenBuffers(1, &id_);
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    glBufferData(GL_ARRAY_BUFFER, values.size() * sizeof(float), values.data(), GL_STATIC_DRAW);

    const auto valuesPerIndex = std::accumulate(valuesPerAttribute.begin(), valuesPerAttribute.end(), 0);

    for(size_t i = 0; i < valuesPerAttribute.size(); ++i)
    {
        const auto valuesBeforeThisAttribute = std::accumulate(&valuesPerAttribute[0], &valuesPerAttribute[i], 0);

        glVertexAttribPointer(i, valuesPerAttribute[i], GL_FLOAT, GL_FALSE, valuesPerIndex * sizeof(float), 
                              reinterpret_cast<void*>(valuesBeforeThisAttribute * sizeof(float)));

        glEnableVertexAttribArray(i);
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

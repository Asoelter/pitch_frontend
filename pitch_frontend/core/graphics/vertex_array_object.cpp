#include "vertex_array_object.h"

#include <glad/glad.h>

unsigned int VertexArrayObject::currentlyBoundId = none;

VertexArrayObject::VertexArrayObject()
    : vao_(0)
{
    glGenVertexArrays(1, &vao_);
    bind();
}

VertexArrayObject::~VertexArrayObject()
{
    unbind();
}

void VertexArrayObject::bind()
{
    glBindVertexArray(vao_);

    currentlyBoundId = vao_;
}

void VertexArrayObject::unbind()
{
    glBindVertexArray(0);

    if(vao_ == currentlyBoundId)
    {
        currentlyBoundId = none;
    }
}

#include "vertex_array_object.h"

#include <glad/glad.h>

unsigned int VertexArrayObject::currentlyBoundVao_ = noVaoIsBound_;

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

    currentlyBoundVao_ = vao_;
}

void VertexArrayObject::unbind()
{
    glBindVertexArray(0);

    if(vao_ == currentlyBoundVao_)
    {
        currentlyBoundVao_ = noVaoIsBound_;
    }
}

#include "mesh.h"

Mesh::Mesh(const VertexBufferObject& vbo)
    : vbo_(vbo)
    , translation_(Mat4::identity())
    , rotation_(Mat4::identity())
{
    
}

void Mesh::translate(const Vec3& direction)
{
    translation_ *= Mat4::translate(direction);
}

void Mesh::rotate(const Vec3& axis, Radian rads)
{
    rotation_ *= Mat4::rotate(axis, rads);
}

void Mesh::rotate(const Vec3& axis, Degree degree)
{
    rotation_ *= Mat4::rotate(axis, degree);
}

Mat4 Mesh::matrix() const noexcept
{
    return rotation_ * translation_;
}

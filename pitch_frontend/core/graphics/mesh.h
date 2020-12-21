#ifndef MESH_H
#define MESH_H

#include <math/mat.h>
#include <math/trig.h>
#include <math/vec.h>

#include "vertex_buffer_object.h"

class Mesh
{
public:
    Mesh(const VertexBufferObject& vbo);

    void translate(const Vec3& direction);
    void rotate(const Vec3& axis, Radian rads);
    void rotate(const Vec3& axis, Degree degree);

    Mat4 matrix() const noexcept;

private:
    VertexBufferObject vbo_;
    Mat4               translation_;
    Mat4               rotation_;
};

#endif //MESH_H

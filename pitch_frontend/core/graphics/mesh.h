#ifndef MESH_H
#define MESH_H

#include <vector>

#include <math/mat.h>
#include <math/trig.h>
#include <math/vec.h>

class Mesh
{
public:
    Mesh(const std::vector<float>& vertices);

    void translate(const Vec3& direction);
    void rotate(Radian rads);
    void rotate(Degree degree);

private:
    Mat4 modelMatrix_;
};

#endif //MESH_H

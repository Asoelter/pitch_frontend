#ifndef CAMERA_H
#define CAMERA_H

#include "math/mat.h"
#include "vec.h"

class Camera
{
public:
    Camera(const Vec3& eye, const Vec3& center, const Vec3& up);
    Camera(const Camera&) = default;
    Camera(Camera&&) = default;
    ~Camera() = default;

    Camera& operator=(const Camera&) = default;
    Camera& operator=(Camera&&) = default;

    void move(const Vec3& direction);
    void zoom(float scale);

    Mat4 matrix() const noexcept;

private:
    Vec3 eye_;
    Vec3 center_;
    Vec3 up_;
};

#endif //CAMERA_H

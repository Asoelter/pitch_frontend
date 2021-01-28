#include "camera.h"

Camera::Orientation Camera::Orientation::normalOrientation(float setback)
{
    Orientation result;

    result.eye = {0.0f, 0.0f, setback};
    result.center = {0.0f, 0.0f, 0.0f};
    result.up = {0.0f, 1.0f, 0.0f};

    return result;
}

Camera::WorldBounds Camera::WorldBounds::equalBounds(float xBound, float yBound, float zBound)
{
    WorldBounds result;

    result.xmin = -1.0f * xBound;
    result.xmax =  1.0f * xBound;
    result.ymin = -1.0f * yBound;
    result.ymax =  1.0f * yBound;
    result.zmin = -1.0f * zBound;
    result.zmax =  1.0f * zBound;

    return result;
}

Camera::Camera(const Orientation& orientation, const WorldBounds& bounds)
    : orientation_(orientation)
    , bounds_(bounds)
    , zoomScale_(1.0f)
{
    
}

void Camera::move(const Vec3& direction)
{
    orientation_.eye += direction;
}

void Camera::moveTo(const Vec3& direction)
{
    orientation_.eye = direction;
}

void Camera::pan(const Vec3& direction)
{
    orientation_.eye += direction;
    orientation_.center += direction;
}

void Camera::panTo(const Vec3& direction)
{
    orientation_.eye[0] = direction[0];
    orientation_.eye[1] = direction[1];

    orientation_.center = direction;
}

void Camera::zoom(float scale)
{
    assert(false && "This method needs to be improved. Must find proper way of scaling in the projection() method");
    zoomScale_ = scale;
}

[[nodiscard]] float Camera::xmin()
{
    return bounds_.xmin;
}

[[nodiscard]] float Camera::xmax()
{
    return bounds_.xmax;
}

[[nodiscard]] float Camera::ymin()
{
    return bounds_.ymin;
}

[[nodiscard]] float Camera::ymax()
{
    return bounds_.ymax;
}

Mat4 Camera::view() const noexcept
{
    return Mat4::lookAt(orientation_.eye, 
                        orientation_.center, 
                        orientation_.up);
}

Mat4 Camera::projection() const noexcept
{
    return Mat4::orthographic(zoomScale_ * bounds_.xmin, zoomScale_ * bounds_.xmax, 
                              zoomScale_ * bounds_.ymin, zoomScale_ * bounds_.ymax, 
                              zoomScale_ * bounds_.zmin, zoomScale_ * bounds_.zmax);
}

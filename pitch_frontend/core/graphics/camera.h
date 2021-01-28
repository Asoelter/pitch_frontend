#ifndef CAMERA_H
#define CAMERA_H

#include <math/mat.h>
#include <math/vec.h>

class Camera
{
public:

    struct Orientation
    {
        Vec3 eye;
        Vec3 center;
        Vec3 up;

        static Orientation normalOrientation(float setback);
    };

    struct WorldBounds
    {
        float xmin;
        float xmax;
        float ymin;
        float ymax;
        float zmin;
        float zmax;

        static WorldBounds equalBounds(float xBound, float yBound, float zBound); //< needs better name
    };

    Camera(const Orientation& orientation, const WorldBounds& bounds);
    Camera(const Camera&) = default;
    Camera(Camera&&) = default;
    ~Camera() = default;

    Camera& operator=(const Camera&) = default;
    Camera& operator=(Camera&&) = default;

    void move(const Vec3& direction);
    void moveTo(const Vec3& direction);
    void pan(const Vec3& direction);
    void panTo(const Vec3& direction);
    [[deprecated]] void zoom(float scale); //< This one needs more work when needed

    [[nodiscard]] float xmin();
    [[nodiscard]] float xmax();
    [[nodiscard]] float ymin();
    [[nodiscard]] float ymax();

    Mat4 view() const noexcept;
    Mat4 projection() const noexcept;

private:
    Orientation orientation_;
    WorldBounds bounds_;
    float       zoomScale_;
};

#endif //CAMERA_H

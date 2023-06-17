#ifndef RAY_H_
#define RAY_H_

#include "vector_3d.h"

namespace rasterizer
{
    class Ray {
    
    public:
        Ray() {}
        Ray(const Point3D& origin, const Vector3D& direction)
            : orig(origin), dir(direction)
        {}

        Point3D origin() const  { return orig; }
        Vector3D direction() const { return dir; }

        Point3D at(float t) const {
            return orig + t*dir;
        }

    public:
        Point3D orig;
        Vector3D dir;
    };
} // namespace rasterizer

#endif
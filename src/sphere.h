#ifndef SPHERE_H_
#define SPHERE_H_

#include "hittable.h"

namespace rasterizer {

    class Sphere : public Hittable {
    public:
        Sphere() {}
        Sphere(Point3D cen, float r) : center(cen), radius(r) {};
        
        bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
    public: 
        Point3D center;
        float radius;
    };
} // namespace rasterizer

#endif
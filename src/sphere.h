#ifndef SPHERE_H_
#define SPHERE_H_

#include "hittable.h"

namespace rasterizer {

    class Sphere : public Hittable {
    public:
        Sphere() {}
        Sphere(Point3D center, float radius) : center{center}, radius{radius} {};
        
        bool hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const override;
    public: 
        Point3D center;
        float radius;
    };
} // namespace rasterizer

#endif
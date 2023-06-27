#ifndef SPHERE_H_
#define SPHERE_H_

#include "hittable.h"

namespace rasterizer {

    class Sphere : public Hittable {
    public:
        Sphere() {}
        Sphere(Point3D center, float radius, std::shared_ptr<Material> material)
            : center{center}, radius{radius}, material{material} {};
        
        bool hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const override;
    public: 
        std::shared_ptr<Material> material;
        Point3D center;
        float radius;
    };
} // namespace rasterizer

#endif
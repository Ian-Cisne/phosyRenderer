#ifndef HITTABLE_H_
#define HITTABLE_H_

#include "ray.h"

namespace rasterizer {

    struct HitRecord {
        Point3D p;
        Vector3D normal;
        float t;    
        bool front_face;

        inline void set_face_normal(const Ray& r, const Vector3D& outward_normal) {
            front_face = dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal :-outward_normal;
        }
        inline void set_face_normal(const Ray& r, const Vector3D&& outward_normal) {
            front_face = dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal :-outward_normal;
        }
    };

    class Hittable {
    public:
        virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
    };

} // namespace rasterizer

#endif
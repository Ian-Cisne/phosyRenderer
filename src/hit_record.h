#ifndef HIT_RECORD_H_
#define HIT_RECORD_H_

#include <memory>

#include "ray.h"

namespace rasterizer {

    class Material;

    struct HitRecord {
        Point3D point;
        Vector3D normal;
        float t;
        std::shared_ptr<Material> material;
        bool front_face;

        inline void set_face_normal(const Ray& ray, const Vector3D& outward_normal) {
            front_face = dot(ray.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal :-outward_normal;
        }
        inline void set_face_normal(const Ray& ray, const Vector3D&& outward_normal) {
            front_face = dot(ray.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal :-outward_normal;
        }
    };
} // namespace rasterizer

#endif
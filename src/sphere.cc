

#include "sphere.h"

namespace rasterizer {

    bool Sphere::hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const {
        
        Vector3D oc = ray.origin() - center;

        auto a = ray.direction().length_squared();
        auto half_b = dot(oc, ray.direction());
        auto c = oc.length_squared() - radius*radius;

        auto discriminant = half_b*half_b - a*c;
        if (discriminant < 0.0f) {
            return false;
        }

        auto sqrtd = std::sqrt(discriminant);

        auto root = (-half_b - sqrtd) / a;
        if (root < t_min || t_max < root) {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || t_max < root) {
                return false;
            }
        }

        record.t = root;
        record.point = ray.at(record.t);   
        record.set_face_normal(ray, ((record.point - center) / radius));


        return true;
    };
    
} // namespace rasterizer
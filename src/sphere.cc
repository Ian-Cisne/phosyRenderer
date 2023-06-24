

#include "sphere.h"

namespace rasterizer {

    bool Sphere::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
        
        Vector3D oc = r.origin() - center;

        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
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

        rec.t = root;
        rec.p = r.at(rec.t);   
        rec.set_face_normal(r, ((rec.p - center) / radius));


        return true;
    };
    
} // namespace rasterizer
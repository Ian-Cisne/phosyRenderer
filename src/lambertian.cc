

#include "lambertian.h"

namespace rasterizer {

    bool Lambertian::scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const {
        auto scatter_direction = record.normal + Vector3D::random_unit_vector();
        
        if (scatter_direction.near_zero()) {
            scatter_direction = record.normal;
        }
        
        scattered = Ray(record.point, scatter_direction);
        attenuation = albedo;
        return true;
    }

} // namespace rasterizer

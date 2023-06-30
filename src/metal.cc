
#include "metal.h"

namespace rasterizer {
    
    bool Metal::scatter(const Ray& input_ray, const HitRecord& record, Color& attenuation, Ray& scattered) const {
        Vector3D reflected = input_ray.direction().unit_vector().reflect(record.normal);
        scattered = Ray(record.point, fuzz ? reflected + fuzz * Vector3D::normal_random_unit_vector() : reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), record.normal) > 0);
    }

} // namespace rasterizer

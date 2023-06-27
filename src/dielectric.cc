

#include "dielectric.h"

namespace rasterizer {

    bool Dielectric::scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const {
        attenuation = Color(1.0, 1.0, 1.0);
        double refraction_ratio = record.front_face ? (1.0/index_of_refraction) : index_of_refraction;

        Vector3D unit_direction = r_in.direction().unit_vector();
        Vector3D refracted = unit_direction.refract(record.normal, refraction_ratio);

        scattered = Ray(record.point, refracted);
        return true;
    }
    
} // namespace rasterizer

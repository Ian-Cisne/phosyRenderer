
#include "dielectric.h"

namespace rasterizer {

    bool Dielectric::scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const {
        attenuation = Color(1.0, 1.0, 1.0);
        double refraction_ratio = record.front_face ? (1.0/index_of_refraction) : index_of_refraction;

        Vector3D unit_direction = r_in.direction().unit_vector();
        float cos_theta = std::fmin(dot(-unit_direction, record.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

        Vector3D direction = 
            refraction_ratio * sin_theta > 1.0 || reflectance(cos_theta, refraction_ratio) > random_decimal()?
            unit_direction.reflect(record.normal) :
            unit_direction.refract(record.normal, refraction_ratio);
        
        scattered = Ray(record.point, direction);
        return true;
    }
    float Dielectric::reflectance(float cosine, float ref_idx) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1-ref_idx) / (1+ref_idx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    }
    
} // namespace rasterizer

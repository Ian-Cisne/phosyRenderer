#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "material.h"

namespace rasterizer {

    class Lambertian : public Material {
    public:
        Lambertian(const Color& a) : albedo(a) {}

        virtual bool scatter(
            const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered
        ) const override;

    public:
        Color albedo;
    };
    
} // namespace rasterizer

#endif
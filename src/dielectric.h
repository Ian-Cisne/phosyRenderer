#ifndef DIELECTRIC_H_
#define DIELECTRIC_H_

#include "material.h"

namespace rasterizer {

    class Dielectric : public Material {
    public:
        Dielectric(float index_of_refraction) : index_of_refraction{index_of_refraction} {}

        virtual bool scatter(
            const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered
        ) const override;

    public:
        float index_of_refraction;
    };
    
} // namespace rasterizer

#endif
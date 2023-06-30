#ifndef METAL_H_
#define METAL_H_

#include "material.h"

namespace rasterizer {

    class Metal : public Material {
    public:
        Metal(const Color& a, float fuzz) : albedo{a}, fuzz{fuzz} {}

        virtual bool scatter(
            const Ray& input_ray, const HitRecord& record, Color& attenuation, Ray& scattered
        ) const override;

    public:
        Color albedo;
        float fuzz;
    };
    
} // namespace rasterizer

#endif
#ifndef METAL_H_
#define METAL_H_

#include "material.h"

namespace rasterizer {

    class Metal : public Material {
    public:
        Metal(const Color& a) : albedo(a) {}

        virtual bool scatter(
            const Ray& input_ray, const HitRecord& record, Color& attenuation, Ray& scattered
        ) const override;

    public:
        Color albedo;
    };
    
} // namespace rasterizer

#endif
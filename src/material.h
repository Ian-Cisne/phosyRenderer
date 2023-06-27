#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "hit_record.h"

namespace rasterizer {

    class Material {
    
    public:
        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
        ) const = 0;
    };

} // namespace rasterizer

#endif
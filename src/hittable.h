#ifndef HITTABLE_H_
#define HITTABLE_H_

#include "hit_record.h"

namespace rasterizer {

    class Hittable {
    public:
        virtual bool hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const = 0;
    };

} // namespace rasterizer

#endif
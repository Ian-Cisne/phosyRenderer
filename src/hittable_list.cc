
#include <memory>
#include <vector>

#include "hittable_list.h"

namespace rasterizer {

    bool HittableList::hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const {
        HitRecord temp_record;
        bool hit_anything = false;
        float closest_so_far = t_max;

        for (const auto& object : objects_) {
            if (object->hit(ray, t_min, closest_so_far, temp_record)) {
                hit_anything = true;
                closest_so_far = temp_record.t;
                record = temp_record;
            }
        }

        return hit_anything;
    }

} // namespace rasterizer
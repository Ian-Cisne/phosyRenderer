#ifndef HITTABLE_LIST_H_
#define HITTABLE_LIST_H_

#include <memory>
#include <vector>

#include "hittable.h"

namespace rasterizer {

    class HittableList : Hittable {
    public:
        HittableList() {}
        HittableList(std::shared_ptr<Hittable> object) { add(object); }

        void clear() { objects_.clear(); }
        void add(std::shared_ptr<Hittable> object) { objects_.push_back(object); }

        virtual bool hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const override;

    private:
        std::vector<std::shared_ptr<Hittable>> objects_;
    };

} // namespace rasterizer

#endif
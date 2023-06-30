
#include <numbers>
#include <format>

#include "camera.h"
#include "logger.h"

namespace rasterizer {

    Camera::Camera(Point3D &&origin, Vector3D &&direction, Vector3D &&vup, float vertical_fov , float aspect_ratio)
        : origin{origin},
        direction{direction.unit_vector()},
        viewport_height{2 * std::tan(vertical_fov * (std::numbers::pi_v<float> / 360))},
        viewport_width{aspect_ratio * viewport_height},
        focal_length{direction.length()} {
            
            auto u = cross(vup, this->direction).unit_vector();
            auto v = cross(this->direction, u);
            horizontal = viewport_width * u;
            vertical = viewport_height * v;
            lower_left_corner = this->origin - this->horizontal/2 - this->vertical/2 - direction;

    }
    
    Ray Camera::rayAt(float u, float v) {
        return Ray (origin, lower_left_corner + u*horizontal + v*vertical - origin);
    }

} // namespace rasterzver
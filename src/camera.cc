
#include "camera.h"

namespace rasterizer {

    Camera::Camera(Point3D &&origin, Vector3D &&direction, float viewport_height , float viewport_width)
        : origin{origin},
        direction{direction},
        viewport_height{viewport_height},
        viewport_width{viewport_width},
        focal_length{direction.length()},
        horizontal{Vector3D(viewport_width, 0, 0)},
        vertical{Vector3D(0, viewport_height, 0)} {
            lower_left_corner = this->origin - this->horizontal/2 - this->vertical/2 - Vector3D(0, 0, this->focal_length);

    }
    
    Ray Camera::rayAt(float u, float v) {
        
        return Ray (origin, lower_left_corner + u*horizontal + v*vertical - origin);
    }

} // namespace rasterzver
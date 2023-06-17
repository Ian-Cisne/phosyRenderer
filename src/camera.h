#ifndef CAMERA_H_
#define CAMERA_H_

#include "ray.h"

namespace rasterizer
{
    class Camera {
    
    public:
        Camera(Point3D &&origin, float viewport_height , float viewport_width, float focal_length = 0)
            : origin{origin}, viewport_height{viewport_height}, viewport_width{viewport_width}, focal_length{focal_length} {}

        friend class Renderer;
    private:
        Point3D origin;
        float viewport_height;
        float viewport_width;
        float focal_length; 
    };
}

#endif
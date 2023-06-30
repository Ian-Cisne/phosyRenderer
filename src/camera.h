#ifndef CAMERA_H_
#define CAMERA_H_

#include "ray.h"

namespace rasterizer
{
    class Camera {
    
    public:
        Camera(Point3D &&origin, Vector3D &&direction, Vector3D &&vup, float vertical_fov , float aspect_ratio);

        Ray rayAt(float u, float v);
        friend class Renderer;
    private:
        Point3D origin;
        Vector3D direction;

        Vector3D horizontal;
        Vector3D vertical;
        Vector3D lower_left_corner;

        float viewport_height;
        float viewport_width;
        float focal_length; 
    };
} // namespace rasterizer

#endif
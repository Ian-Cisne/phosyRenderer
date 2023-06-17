

#include "renderer.h"

#include <lodepng.h>

namespace rasterizer
{
    Renderer::Renderer(Camera &&camera, unsigned int image_height, unsigned int image_width) 
        : camera{camera}, image_height{image_height}, image_width{image_width}, logger_{Logger::getLogger()} {
        buffer.reserve(image_height * image_width * 3);
    }

    void Renderer::render() {
        //Camera will be pointig towards -Z.
        Vector3D lower_left_corner = camera.origin - camera.horizontal/2 - camera.vertical/2 - Vector3D(0, 0, camera.focal_length);
        for (int j = image_height-1; j >= 0; --j) {
            for (int i = 0; i < image_width; ++i) {
                float u = float(i) / (image_width-1);
                float v = float(j) / (image_height-1);
                Ray ray = camera.rayAt(u, v);
                Color pixel_color = compute_pixel_color(ray);
                commit_color(pixel_color);
            }
        }
        write_image();
    }

    Color Renderer::compute_pixel_color(Ray &ray) {
        if (collision_detection(ray)) {
            return Color(1, 0, 0);
        }

        Vector3D unit_direction = ray.direction().unit_vector();
        auto t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }

    void Renderer::commit_color(Color color) {
        buffer.insert(buffer.end(), {
            static_cast<unsigned char>(color.r()*255.9999),
            static_cast<unsigned char>(color.g()*255.9999),
            static_cast<unsigned char>(color.b()*255.9999)
            });
    }

    void Renderer::write_image() {
        if (unsigned int error_code = lodepng::encode("imagen.png", buffer, image_width, image_height, LCT_RGB)) {
            logger_ << rasterizer::LogLevel::kError << "Encoder error " << error_code << ": "<< lodepng_error_text(error_code) << "\n";
        } else {
            logger_ << rasterizer::LogLevel::kInfo << "Image rendered succesfully!" << "\n";
        }
    }

    bool Renderer::collision_detection(Ray &ray) {
        auto center = Point3D(0,0,-1);
        float radius = 0.5;

        Vector3D oc = ray.origin() - center;
        auto a = dot(ray.direction(), ray.direction());
        auto b = 2.0 * dot(oc, ray.direction());
        auto c = dot(oc, oc) - radius*radius;
        auto discriminant = b*b - 4*a*c;

        return (discriminant > 0);
    }
}

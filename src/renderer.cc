

#include "renderer.h"

#include <lodepng.h>

namespace rasterizer
{
    Renderer::Renderer(Camera cam, unsigned int image_height, unsigned int image_width) 
        : cam{cam}, image_height{image_height}, image_width{image_width}, logger_{Logger::getLogger()} {
        buffer.reserve(image_height * image_width * 3);
    }
    
    void Renderer::render() {
        
        auto horizontal = Vector3D(cam.viewport_width, 0, 0);
        auto vertical = Vector3D(0, cam.viewport_height, 0);
        auto lower_left_corner = cam.origin - horizontal/2 - vertical/2 - Vector3D(0, 0, cam.focal_length);
        for (int j = image_height-1; j >= 0; --j) {
            for (int i = 0; i < image_width; ++i) {
                auto u = double(i) / (image_width-1);
                auto v = double(j) / (image_height-1);
                Ray ray(cam.origin, lower_left_corner + u*horizontal + v*vertical - cam.origin);
                Color pixel_color = compute_pixel_color(ray);
                commit_color(pixel_color);
            }
        }
        unsigned int error_code;
        if (error_code = lodepng::encode("imagen.png", buffer, image_width, image_height, LCT_RGB)) {
            logger_ << rasterizer::LogLevel::kError << "Encoder error " << error_code << ": "<< lodepng_error_text(error_code) << "\n";
        } else {
            logger_ << rasterizer::LogLevel::kInfo << "Image rendered succesfully!" << "\n";
        }
    }

    Color Renderer::compute_pixel_color(Ray ray) {
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
}

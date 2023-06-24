
#include "renderer.h"

#include <lodepng.h>

namespace rasterizer {

    Renderer::Renderer(Camera &&camera, unsigned int image_height, unsigned int image_width) 
        : camera{camera}, image_height{image_height}, image_width{image_width}, logger_{Logger::getLogger()} {
        buffer.reserve(image_height * image_width * 3u);
    }

    void Renderer::render() {

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
        float t = collision_detection(ray);
        if (t > 0.0f) {
            Vector3D normal = (ray.at(t) - Vector3D(0.0f, 0.0f, -2.0f)).unit_vector();
            return 0.5 * Color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
        }

        Vector3D unit_direction = ray.direction().unit_vector();
        t = 0.5f * (unit_direction.y() + 1.0f);
        return (1.0f - t) * Color(1.0f, 1.0f, 1.0f) + t * Color(0.5f, 0.7f, 1.0f);
    }

    void Renderer::commit_color(Color color) {
        buffer.insert(buffer.end(), {
            static_cast<unsigned char>(color.r() * 255.9999847f),
            static_cast<unsigned char>(color.g() * 255.9999847f),
            static_cast<unsigned char>(color.b() * 255.9999847f)
            });
    }

    void Renderer::write_image() {
        if (unsigned int error_code = lodepng::encode("imagen.png", buffer, image_width, image_height, LCT_RGB)) {
            logger_ << rasterizer::LogLevel::kError << "Encoder error " << error_code << ": "<< lodepng_error_text(error_code) << "\n";
        } else {
            logger_ << rasterizer::LogLevel::kInfo << "Image rendered succesfully!" << "\n";
        }
    }

    float Renderer::collision_detection(Ray &ray) {
        auto center = Point3D(0.0f, 0.0f, -2.0f);
        float radius = 0.5f;

        Vector3D oc = ray.origin() - center;
        auto a = ray.direction().length_squared();
        auto half_b = dot(oc, ray.direction());
        auto c = oc.length_squared() - radius*radius;
        auto discriminant = half_b*half_b - a*c;
            return (discriminant < 0.0f) 
                ? -1.0f 
                : (-half_b - sqrt(discriminant) ) / a;
    }

}

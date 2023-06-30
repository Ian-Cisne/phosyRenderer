
#include "material.h"
#include "renderer.h"

#include <lodepng.h>

namespace rasterizer {


    Renderer::Renderer(Camera &&camera, unsigned int image_height, unsigned int image_width) 
        : camera{camera}, 
        image_height{image_height}, 
        image_width{image_width}, 
        logger_{Logger::getLogger()}, 
        samples_per_pixel{30},
        max_depth{40}{
        buffer.reserve(image_height * image_width * 3u);
    }

    void Renderer::render() {

        for (int j = image_height-1; j >= 0; --j) {
            for (int i = 0; i < image_width; ++i) {
                Color pixel_color(0.0f, 0.0f, 0.0f);
                for (unsigned char p = 0;  p < samples_per_pixel; p++) {
                    float u = (float(i) + random_decimal()) / (image_width-1);
                    float v = (float(j) + random_decimal()) / (image_height-1);
                    Ray ray = camera.rayAt(u, v);
                    current_depth_ = max_depth;
                    pixel_color += compute_pixel_color(ray);
                }
                commit_color(sqrt(pixel_color * (1.0f / samples_per_pixel)));
            }
        }

        write_image();
    }

    Color Renderer::compute_pixel_color(Ray &ray) {
        if (current_depth_ == 0) {
            return {0.0f, 1.0f, 0.0f};
        }
        current_depth_--;

        HitRecord record;
        if (world_.hit(ray, 0.001f, 300.0f, record)) {
            Ray scattered;
            Color attenuation;
            if (record.material->scatter(ray, record, attenuation, scattered)) {
                return attenuation * compute_pixel_color(scattered);
            }
            return Color(0,0,0);
        }

        Vector3D unit_direction = ray.direction().unit_vector();
        record.t = 0.5f * (unit_direction.y() + 1.0f);
        return ((1.0f - record.t) * Color(1.0f, 1.0f, 1.0f) + record.t * Color(0.5f, 0.7f, 1.0f)) ;
    }

    void Renderer::commit_color(Color &&color) {
        auto a = color.rgb();
        buffer.insert(buffer.end(),a.begin(), a.end());
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
                : (-half_b - std::sqrt(discriminant) ) / a;
    }

    void Renderer::addHittable(std::shared_ptr<Hittable> object) {
        world_.add(object);
    }

}

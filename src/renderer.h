#ifndef RENDERER_H_
#define RENDERER_H_

#include <vector>

#include "camera.h"
#include "logger.h"
#include "hittable_list.h"

namespace rasterizer {

    class Renderer {
    
    public:
        Renderer(Camera &&camera, unsigned int image_height, unsigned int image_width);

        void addHittable(std::shared_ptr<Hittable> object);

        void setSamplesPerPixel(unsigned char quantity) { samples_per_pixel = quantity; }

        void render();
    private:
        Camera camera;
        Logger& logger_;

        HittableList world_;

        unsigned char samples_per_pixel;
        float ratio_of_pixel_color;
        std::vector<unsigned char> buffer;
        unsigned int image_height;
        unsigned int image_width;

        unsigned char max_depth;
        unsigned char current_depth_; 


        Color compute_pixel_color(Ray &ray);
        void commit_color(Color &&color);
        void write_image();
        float collision_detection(Ray &ray);
    };

} // namespace rasterizer

#endif
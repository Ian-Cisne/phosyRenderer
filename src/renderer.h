#ifndef RENDERER_H_
#define RENDERER_H_

#include <vector>

#include "camera.h"
#include "logger.h"

namespace rasterizer
{
    class Renderer {
    
    public:
        Renderer(Camera cam, unsigned int image_height, unsigned int image_width);

        void render();
    private:
        Camera cam;
        Logger& logger_;
        std::vector<unsigned char> buffer;
        unsigned int image_height;
        unsigned int image_width;

        Color compute_pixel_color(Ray ray);
        void commit_color(Color);
    };
}

#endif
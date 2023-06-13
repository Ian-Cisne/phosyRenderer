
#include <stdlib.h>

#include <iostream> 
#include <vector> 

#include "logger.h"

#include <lodepng.h>

int main(int /*argc*/, char ** /*argv*/) {

    rasterizer::Logger& logger = rasterizer::Logger::getLogger(std::cerr);

    logger << rasterizer::LogLevel::kInfo << "iniciando\n";
    
    unsigned int 
        height= 512,
        width = 512;

    std::vector<unsigned char> image;
    image.resize(height * width * 4);
    for (int j = height-1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            auto r = float(i) / (width-1);
            auto g = float(j) / (height-1);
            auto b = 0.25;

            image[4 * width * j + 4 * i + 0] = static_cast<unsigned char>(255.999 * r);
            image[4 * width * j + 4 * i + 1] = static_cast<unsigned char>(255.999 * g);
            image[4 * width * j + 4 * i + 2] = static_cast<unsigned char>(255.999 * b);
            image[4 * width * j + 4 * i + 3] = 255;

        }
    }
    if (lodepng::encode("imagen.png", image, width, height)) {
        logger << rasterizer::LogLevel::kInfo << "if de imagen";
    }
    return EXIT_SUCCESS;
}
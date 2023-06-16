
#include <stdlib.h>

#include <iostream> 
#include <vector> 

#include "logger.h"
#include "vector_3d.h"

#include <lodepng.h>

int main(int /*argc*/, char ** /*argv*/) {

    rasterizer::Logger& logger = rasterizer::Logger::getLogger(std::cerr);

    logger << rasterizer::LogLevel::kInfo << "Intiating...\n";
    
    unsigned int 
        height= 512,
        width = 512;
    logger << rasterizer::LogLevel::kInfo << "Rendering image...\n";

    std::vector<unsigned char> image;
    for (int j = height-1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            rasterizer::Color pixel(float(i) / (width-1), float(j) / (height-1), 0.25f);
            auto color = pixel.rgb();
            image.insert(image.end(), color.begin(), color.end());

        }
    }
    unsigned int errorCode;
    if (errorCode = lodepng::encode("imagen.png", image, width, height, LCT_RGB)) {
        logger << rasterizer::LogLevel::kError << "Encoder error " << errorCode << ": "<< lodepng_error_text(errorCode) << "\n";
    } else {
        logger << rasterizer::LogLevel::kInfo << "Image rendered succesfully!" << "\n";
    }
    return EXIT_SUCCESS;
}
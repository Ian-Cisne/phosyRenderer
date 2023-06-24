
#include <stdlib.h>

#include <iostream> 
#include <vector> 

#include "renderer.h"


int main(int /*argc*/, char ** /*argv*/) {

    rasterizer::Logger& logger = rasterizer::Logger::getLogger(std::cerr);

    logger << rasterizer::LogLevel::kInfo << "Intiating...\n";

    constexpr float aspect_ratio  = 16.0f / 9.0f;
    constexpr unsigned int height= 400;
    constexpr unsigned int width = height * aspect_ratio;

    rasterizer::Renderer renderer( 
        rasterizer::Camera(
            rasterizer::Point3D(0.0f, 0.0f, 0.0f),
            rasterizer::Vector3D(1.0f, 0.0f, -1.0f),
            2.0f,
            2.0f * aspect_ratio
        ), 
        height, 
        width);
    
    renderer.render();
    
    return EXIT_SUCCESS;
}
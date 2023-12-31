
#include <stdlib.h>

#include <iostream>
#include <vector>
#include <memory>

#include "renderer.h"
#include "metal.h"
#include "lambertian.h"
#include "dielectric.h"
#include "sphere.h"


int main(int argc, char ** argv) {

    rasterizer::Logger& logger = rasterizer::Logger::getLogger(std::cerr);

    logger << rasterizer::LogLevel::kInfo << "Intiating...\n";

    constexpr float aspect_ratio = 16.0f / 9.0f;
    constexpr unsigned int height= 500;
    constexpr unsigned int width = height * aspect_ratio;


    auto material_ground = std::make_shared<rasterizer::Lambertian>(rasterizer::Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<rasterizer::Lambertian>(rasterizer::Color(0.7, 1, 0.3));
    auto material_left = std::make_shared<rasterizer::Dielectric>(1.2f);
    auto material_right   = std::make_shared<rasterizer::Metal>(rasterizer::Color(0.8, 0.8, 0.8), 0.0f);

    rasterizer::Renderer renderer(
        rasterizer::Camera(
            rasterizer::Point3D(5.0f, 3.0f, 0.0f),
            rasterizer::Vector3D(1.0f, 1.0f, 1.0f),
            rasterizer::Vector3D(0.0f, 1.0f, 0.0f),
            90.0f,
            aspect_ratio
        ),
        height,
        width);

    renderer.addHittable(
        std::make_shared<rasterizer::Sphere>(
            rasterizer::Point3D(0.0f, -10.5f, -1.0f),
            10.0f,
            material_ground
        )
    );
    renderer.addHittable(
        std::make_shared<rasterizer::Sphere>(
            rasterizer::Point3D(-0.2f, 0.0f, -1.0f),
            0.5f,
            material_right
        )
    );
    renderer.addHittable(
        std::make_shared<rasterizer::Sphere>(
            rasterizer::Point3D(0.8f, -0.2f, -1.5f),
            0.2f,
            material_left
        )
    );
    renderer.addHittable(
        std::make_shared<rasterizer::Sphere>(
            rasterizer::Point3D(2.5f, 2.0f, -3.0f),
            1.0f,
            material_center
        )
    );
    renderer.render();

    return EXIT_SUCCESS;
}

#include "vector_3d.h"

namespace rasterizer {

    float random_decimal(){
        static std::uniform_real_distribution<float> distribution(0.0, 1.0);
        static std::default_random_engine generator;
        return distribution(generator);
    }

    float random_decimal(float min, float max) {
        return (max - min) * random_decimal() + min;
    }
    
    Vector3D Vector3D::random_unit_vector() {
        static std::uniform_real_distribution<float> distribution(0.0, 2.0);
        static std::default_random_engine generator;
        float phi = distribution(generator);
        float theta = distribution(generator);
        float thetasin = sin(theta); 
        return Vector3D( thetasin * cos(phi), thetasin * sin(phi), cos(theta));
    }
} // namespace rasteriver

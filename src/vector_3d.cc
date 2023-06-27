
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

    Vector3D sqrt(const Vector3D &a) {
        return {std::sqrt(a.values_[0]), std::sqrt(a.values_[1]), std::sqrt(a.values_[2])};
    }
    
    bool Vector3D::near_zero() {
        constexpr auto s = 1e-8;
        return (std::fabs(values_[0]) < s) && (std::fabs(values_[1]) < s) && (std::fabs(values_[2]) < s);
    }

    Vector3D Vector3D::reflect(const Vector3D& normal) {
        return *this - 2*dot(*this, normal)*normal;
    }

    Vector3D Vector3D::refract(const Vector3D& n, double etai_over_etat) {
        auto cos_theta = std::fmin(dot(-(*this), n), 1.0);
        Vector3D r_out_perp =  etai_over_etat * ((*this) + cos_theta*n);
        Vector3D r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
        return r_out_perp + r_out_parallel;
    }

    Vector3D &Vector3D::operator =(const Vector3D &a) {
        values_[0] = a.values_[0]; values_[1] = a.values_[1]; values_[2] = a.values_[2];
        return *this;
    }

    bool Vector3D::operator ==(const Vector3D &a) const {
        return values_[0]==a.values_[0] && values_[1]==a.values_[1] && values_[2]==a.values_[2];
    }

    bool Vector3D::operator !=(const Vector3D &a) const {
        return values_[0]!=a.values_[0] || values_[1]!=a.values_[1] || values_[2]!=a.values_[2];
    }

    void Vector3D::toZero() { values_[0] = values_[1] = values_[2] = 0.0f; }

    Vector3D Vector3D::operator -() const { return Vector3D(-values_[0],-values_[1],-values_[2]); }

    Vector3D Vector3D::operator +(const Vector3D &a) const {
        return Vector3D(values_[0] + a.values_[0], values_[1] + a.values_[1], values_[2] + a.values_[2]);
    }

    Vector3D Vector3D::operator *(const Vector3D &a) const {
        return Vector3D(values_[0] * a.values_[0], values_[1] * a.values_[1], values_[2] * a.values_[2]);
    }

    Vector3D Vector3D::operator -(const Vector3D &a) const {
        return Vector3D(values_[0] - a.values_[0], values_[1] - a.values_[1], values_[2] - a.values_[2]);
    }

    Vector3D Vector3D::operator *(float a) const {
        return Vector3D(values_[0]*a, values_[1]*a, values_[2]*a);
    }

    //You should not unse it with zero.
    Vector3D Vector3D::operator /(float a) const {
        float oneOverA = 1.0f / a; 
        return Vector3D(values_[0]*oneOverA, values_[1]*oneOverA, values_[2]*oneOverA);
    }

    Vector3D &Vector3D::operator +=(const Vector3D &a) {
        values_[0] += a.values_[0]; values_[1] += a.values_[1]; values_[2] += a.values_[2];
        return *this;
    }

    Vector3D &Vector3D::operator -=(const Vector3D &a) {
        values_[0] -= a.values_[0]; values_[1] -= a.values_[1]; values_[2] -= a.values_[2];
        return *this;
    }

    Vector3D &Vector3D::operator *=(float a) {
        values_[0] *= a; values_[1] *= a; values_[2] *= a;
        return *this;
    }

    Vector3D &Vector3D::operator /=(float a) {
        float oneOverA = 1.0f / a;
        values_[0] *= oneOverA; values_[1] *= oneOverA; values_[2] *= oneOverA;
        return *this;
    }

    Vector3D Vector3D::unit_vector() {
        return *this / length();
    }

    float Vector3D::length() const {
        return std::sqrt(values_[0]*values_[0] + values_[1]*values_[1] + values_[2]*values_[2]);
    }

    float Vector3D::length_squared() const {
        return values_[0]*values_[0] + values_[1]*values_[1] + values_[2]*values_[2];
    }
    
} // namespace rasteriver

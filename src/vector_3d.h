#ifndef VECTOR_3D_H_
#define VECTOR_3D_H_

#include <ostream>
#include <array>
#include <random>

#include <math.h>

namespace rasterizer {

    float random_decimal();

    float random_decimal(float min, float max);

    class Vector3D {
    private:

    public:
        static Vector3D uniform_random_unit_vector();
        static Vector3D normal_random_unit_vector();

        float& r() { return values_[0]; }
        float& g() { return values_[1]; }
        float& b() { return values_[2]; }

        std::array<unsigned char, 3> rgb() { return {
            static_cast<unsigned char>(values_[0]*255.9999999000000059),
            static_cast<unsigned char>(values_[1]*255.9999999000000059),
            static_cast<unsigned char>(values_[2]*255.9999999000000059)
            }; }
        
        float& x() { return values_[0]; }
        float& y() { return values_[1]; }
        float& z() { return values_[2]; }

        auto begin() {return std::begin(values_);}
        auto end() {return std::end(values_);}

        Vector3D() {}
        
        Vector3D(const Vector3D &a) {
            values_[0] = a.values_[0]; values_[1] = a.values_[1]; values_[2] = a.values_[2];
        }

        Vector3D(float nx, float ny, float nz) : values_{nx, ny, nz} {}

        bool near_zero();

        Vector3D reflect(const Vector3D& normal);

        Vector3D refract(const Vector3D& n, double etai_over_etat);

        void toZero();

        Vector3D &operator =(const Vector3D &a);

        bool operator ==(const Vector3D &a) const;

        bool operator !=(const Vector3D &a) const;

        Vector3D operator -() const;

        Vector3D operator +(const Vector3D &a) const;

        Vector3D operator -(const Vector3D &a) const;

        Vector3D operator *(const Vector3D &a) const;

        Vector3D operator *(float a) const;

        //You should not use it with zero.
        Vector3D operator /(float a) const;

        Vector3D &operator +=(const Vector3D &a);

        Vector3D &operator -=(const Vector3D &a);

        Vector3D &operator *=(float a);

        //You should not use it with zero.
        Vector3D &operator /=(float a);

        Vector3D unit_vector();

        float length() const;

        float length_squared() const;
    
    public:

        float values_[3];
    };
    
    inline std::ostream& operator<<(std::ostream &out, const Vector3D &v) {
        return out << v.values_[0] << ' ' << v.values_[1] << ' ' << v.values_[2];
    }

    inline Vector3D cross(const Vector3D &a, const Vector3D &b) {
        return Vector3D(
            a.values_[1]*b.values_[2] - a.values_[2]*b.values_[1],
            a.values_[2]*b.values_[0] - a.values_[0]*b.values_[2],
            a.values_[0]*b.values_[1] - a.values_[1]*b.values_[0]
        );
    }

    inline float dot(const Vector3D &a, const Vector3D &b) {
        return a.values_[0] * b.values_[0]
         + a.values_[1] * b.values_[1]
         + a.values_[2] * b.values_[2];
    }

    inline Vector3D operator*(float a, const Vector3D &b) {
            return Vector3D(b.values_[0]*a, b.values_[1]*a, b.values_[2]*a);
    }

    //You should not use it with zero.
    inline Vector3D operator /(float a, const Vector3D &b) {
        float oneOverA = 1.0f / a; 
        return Vector3D(b.values_[0]*oneOverA, b.values_[1]*oneOverA, b.values_[2]*oneOverA);
    }
    
    
    inline float distance(const Vector3D &a, const Vector3D &b) {
        float dx = a.values_[0] - b.values_[0];
        float dy = a.values_[1] - b.values_[1];
        float dz = a.values_[2] - b.values_[2];
        return std::sqrt(dx*dx + dy*dy + dz*dz);
    }
    Vector3D sqrt(const Vector3D &a);
    using Point3D = Vector3D;   // 3D point
    using Color = Vector3D;   // RGB Color

} // namespace rasteriver

#endif
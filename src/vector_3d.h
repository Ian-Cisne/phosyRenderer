#ifndef VECTOR3D_H_
#define VECTOR3D_H_

#include <ostream>
#include <array>

#include <math.h>

namespace rasterizer
{
    class Vector3D {
    
    public:
        
        float& r() { return values_[0]; }
        float& g() { return values_[1]; }
        float& b() { return values_[2]; }
        std::array<unsigned char, 3> rgb() { return {
            static_cast<unsigned char>(values_[0]*255.99),
            static_cast<unsigned char>(values_[1]*255.99),
            static_cast<unsigned char>(values_[2]*255.99)
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

        Vector3D &operator =(const Vector3D &a) {
            values_[0] = a.values_[0]; values_[1] = a.values_[1]; values_[2] = a.values_[2];
            return *this;
        }
        bool operator ==(const Vector3D &a) const {
            return values_[0]==a.values_[0] && values_[1]==a.values_[1] && values_[2]==a.values_[2];
        }
        bool operator !=(const Vector3D &a) const {
            return values_[0]!=a.values_[0] || values_[1]!=a.values_[1] || values_[2]!=a.values_[2];
        }

        void toZero() { values_[0] = values_[1] = values_[2] = 0.0f; }

        Vector3D operator -() const { return Vector3D(-values_[0],-values_[1],-values_[2]); }

        Vector3D operator +(const Vector3D &a) const {
            return Vector3D(values_[0] + a.values_[0], values_[1] + a.values_[1], values_[2] + a.values_[2]);
        }
        Vector3D operator -(const Vector3D &a) const {
            return Vector3D(values_[0] - a.values_[0], values_[1] - a.values_[1], values_[2] - a.values_[2]);
        }

        Vector3D operator *(float a) const {
            return Vector3D(values_[0]*a, values_[1]*a, values_[2]*a);
        }
        //You should not unse it with zero.
        Vector3D operator /(float a) const {
            float oneOverA = 1.0f / a; 
            return Vector3D(values_[0]*oneOverA, values_[1]*oneOverA, values_[2]*oneOverA);
        }
        Vector3D &operator +=(const Vector3D &a) {
            values_[0] += a.values_[0]; values_[1] += a.values_[1]; values_[2] += a.values_[2];
            return *this;
        }
        Vector3D &operator -=(const Vector3D &a) {
            values_[0] -= a.values_[0]; values_[1] -= a.values_[1]; values_[2] -= a.values_[2];
            return *this;
        }
        Vector3D &operator *=(float a) {
            values_[0] *= a; values_[1] *= a; values_[2] *= a;
            return *this;
        }
        Vector3D &operator /=(float a) {
            float oneOverA = 1.0f / a;
            values_[0] *= oneOverA; values_[1] *= oneOverA; values_[2] *= oneOverA;
            return *this;
        }
        double length() const {
            return std::sqrt(values_[0]*values_[0] + values_[1]*values_[1] + values_[2]*values_[2]);
        }
        friend inline std::ostream& operator<<(std::ostream &, const Vector3D &);
        friend inline Vector3D cross(const Vector3D &a, const Vector3D &b);
        friend inline float distance(const Vector3D &a, const Vector3D &b);
    private:
        
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
    
    inline float distance(const Vector3D &a, const Vector3D &b) {
        float dx = a.values_[0] - b.values_[0];
        float dy = a.values_[1] - b.values_[1];
        float dz = a.values_[2] - b.values_[2];
        return sqrt(dx*dx + dy*dy + dz*dz);
    }
    using Point3D = Vector3D;   // 3D point
    using Color = Vector3D;   // RGB Color
}
#endif
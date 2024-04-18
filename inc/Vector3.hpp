#pragma once
#include <math.h>
#include <cmath>
class Vector3
{
public:
    float x;
    float y;
    float z;

    Vector3(float _x=0, float _y=0, float _z=0);
    ~Vector3();


    Vector3 operator-(const Vector3 &rhs) {
        return (Vector3(this->x-rhs.x, this->y-rhs.y, this->z-rhs.z));
    }

    float magnitude() const noexcept {
        return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    }

    Vector3 unitvector() const noexcept {
        const float denominator = magnitude();
        return Vector3{
            x/denominator,
            y/denominator,
            z/denominator
        };
    }

    Vector3 add(const Vector3& inputvctr) const noexcept {
        return Vector3 {
            this->x + inputvctr.x, 
                this->y + inputvctr.y, 
                this->z + inputvctr.z
        };
    }

    Vector3 scale(const float& scale) const noexcept {
        return Vector3 {
            x * scale,
            y * scale,
            z * scale
        };
    }


    Vector3& operator+=(const Vector3& right) noexcept {
        return *this = this->add(right);
    }

    Vector3 operator*(const float& right) const noexcept {
        return this->scale(right);
    }

    Vector3& operator*=(const float& right) noexcept {
        return *this = this->scale(right);
    }

    float operator[](const int& index) const {
        switch (index) {
            case 0:
                return this->x;
                break;
            case 1:
                return this->y;
                break;
            case 2:
                return this->z;
                break;
            default:
                throw index;
        }
    }
};

Vector3::Vector3(float _x=0, float _y=0, float _z=0) : x(_x), y(_y), z(_z)
{
}

Vector3::~Vector3()
{
}

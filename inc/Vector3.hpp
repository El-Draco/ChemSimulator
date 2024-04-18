#pragma once
#include <math.h>
#include <cmath>
#include <iostream>
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342

class Vector3
{
public:
    float x;
    float y;
    float z;

    Vector3(float _x, float _y, float _z);
    ~Vector3();


    Vector3 subtract(const Vector3& inputvctr) const noexcept;
    float dotproduct(const Vector3& inputvctr) const noexcept; 
    Vector3 crossproduct(const Vector3& inputvctr) const noexcept;
    float angle(const Vector3 &inputvctr) const noexcept;

    Vector3 rodrigues_rotate(const Vector3& axisvector, const float& angle) const noexcept;
    
    Vector3 operator-(const Vector3 &rhs);

    float magnitude() const noexcept;

    Vector3 unitvector() const noexcept;

    Vector3 add(const Vector3 &inputvctr) const noexcept;

    Vector3 scale(const float &scale) const noexcept;
    Vector3 &operator+=(const Vector3 &right) noexcept;

    Vector3 operator*(const float &right) const noexcept;

    Vector3 &operator*=(const float &right) noexcept;

    float operator[](const int &index) const;
    friend std::ostream &operator<<(std::ostream &os, const Vector3 &m);

};
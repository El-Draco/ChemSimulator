#include "Vector3.hpp"

Vector3::Vector3(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z)
{
}
Vector3::~Vector3()
{
}

Vector3 Vector3::subtract(const Vector3 &inputvctr) const noexcept
{
    return Vector3{
        this->x - inputvctr.x,
        this->y - inputvctr.y,
        this->z - inputvctr.z};
}

float Vector3::dotproduct(const Vector3 &inputvctr) const noexcept
{
    return (x * inputvctr.x) + (y * inputvctr.y) + (z * inputvctr.z);
}

Vector3 Vector3::crossproduct(const Vector3 &inputvctr) const noexcept
{
    return Vector3{
        this->y * inputvctr.z - this->z * inputvctr.y, this->z * inputvctr.x - this->x * inputvctr.z, this->x * inputvctr.y - this->y * inputvctr.x};
}

Vector3 Vector3::rodrigues_rotate(const Vector3 &axisvector, const float &angle) const noexcept
{
    Vector3 Uaxisvector = axisvector.unitvector();
    Vector3 Uthis = this->unitvector();
    return Uthis.subtract(Uaxisvector.scale(Uaxisvector.dotproduct(Uthis))).scale(cos(angle)).add(Uaxisvector.crossproduct(Uthis).scale(sin(angle))).add(Uaxisvector.scale(Uaxisvector.dotproduct(Uthis))).scale(this->magnitude());
}
Vector3 Vector3::operator-(const Vector3 &rhs)
{
    return (Vector3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z));
}

float Vector3::magnitude() const noexcept
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

float Vector3::angle(const Vector3 &inputvctr) const noexcept
{
    return acos(dotproduct(inputvctr) / this->magnitude() * inputvctr.magnitude()) * (180 / PI);
}
Vector3 Vector3::unitvector() const noexcept
{
    const float denominator = magnitude();
    return Vector3{
        x / denominator,
        y / denominator,
        z / denominator};
}

Vector3 Vector3::add(const Vector3 &inputvctr) const noexcept
{
    return Vector3{
        this->x + inputvctr.x,
        this->y + inputvctr.y,
        this->z + inputvctr.z};
}

Vector3 Vector3::scale(const float &scale) const noexcept
{
    return Vector3{
        x * scale,
        y * scale,
        z * scale};
}

Vector3 &Vector3::operator+=(const Vector3 &right) noexcept
{
    return *this = this->add(right);
}

Vector3 Vector3::operator*(const float &right) const noexcept
{
    return this->scale(right);
}

Vector3 &Vector3::operator*=(const float &right) noexcept
{
    return *this = this->scale(right);
}

float Vector3::operator[](const int &index) const
{
    switch (index)
    {
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

std::ostream &operator<<(std::ostream &os, const Vector3 &m)
{
    os << '(' << m.x << ", " << m.y << ", " << m.z << ')' << '\n';
    return (os);
}
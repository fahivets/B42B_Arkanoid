#include "stdafx.h"
#include "Vector2f.h"

// Constructors/Destructors

Vector2f::Vector2f(float xValue, float yValue) : x(xValue), y(yValue)
{}

Vector2f& Vector2f::add(const Vector2f & vec)
{
    x += vec.x;
    y += vec.y;
    return (*this);
}

Vector2f& Vector2f::subtract(const Vector2f& vec)
{
    x -= vec.x;
    y -= vec.y;
    return (*this);
}

Vector2f& Vector2f::multiply(const Vector2f& vec)
{
    x *= vec.x;
    y *= vec.y;
    return (*this);
}

Vector2f& Vector2f::divide(const Vector2f& vec)
{
    x /= vec.x;
    y /= vec.y;
    return (*this);
}

// Overloaded operator functions
Vector2f& operator+(Vector2f& vec1, const Vector2f& vec2)
{
    Vector2f vec = vec1;
    return (vec.add(vec2));
}

Vector2f& operator-(Vector2f& vec1, const Vector2f& vec2)
{
    Vector2f vec = vec1;
    return (vec.subtract(vec2));
}

Vector2f& operator/(Vector2f& vec1, const Vector2f& vec2)
{
    Vector2f vec = vec1;
    return (vec.divide(vec2));
}

Vector2f& operator*(Vector2f& vec1, const Vector2f& vec2)
{
    Vector2f vec = vec1;
    return (vec.multiply(vec2));
}
// TEST
Vector2f& operator/(Vector2f& vec1, const float& val)
{
    return (vec1.divide({ val, val }));
}

Vector2f& operator*(Vector2f& vec1, const float& val)
{
    return (vec1.multiply({val, val}));
}

std::ostream& operator<<(std::ostream& out, const Vector2f& vec)
{
    out << "(" << vec.x << ", " << vec.y << ")";
    return (out);
}

Vector2f& Vector2f::operator+=(const Vector2f& vec)
{
    return (this->add(vec));
}

Vector2f& Vector2f::operator-=(const Vector2f& vec)
{
    return (this->subtract(vec));
}

Vector2f& Vector2f::operator/=(const Vector2f& vec)
{
    return (this->divide(vec));
}

Vector2f& Vector2f::operator*=(const Vector2f& vec)
{
    return (this->multiply(vec));
}

// Scalar operations
Vector2f& Vector2f::operator/=(const float& val)
{
    x /= val;
    y /= val;
    return (*this);
}

Vector2f& Vector2f::operator*=(const float& val)
{
    x *= val;
    y *= val;
    return (*this);
}

float Vector2f::magnitudeSqrt() const
{
    return (x * x + y * y);
}

float Vector2f::magnitude() const
{
    return (static_cast<float>(sqrt(magnitudeSqrt())));
}

Vector2f Vector2f::normalize()
{
    float mag = magnitude();
    return (Vector2f(x / mag, y / mag));
}
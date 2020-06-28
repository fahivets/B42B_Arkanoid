#ifndef B42B_VECTOR2F_H
#define B42B_VECTOR2F_H

/*
    TODO check and change methids: 
    - multiply
    - divide
*/

struct Vector2f
{
    // Variables
    float x;
    float y;

    // Constructors/Destructors
    Vector2f(float xValue = 0.0f, float yValue = 0.0f);
    ~Vector2f() = default;

    Vector2f& add(const Vector2f& vec);
    Vector2f& subtract(const Vector2f& vec);
    Vector2f& multiply(const Vector2f& vec);
    Vector2f& divide(const Vector2f& vec);

    // Overloaded operator functions
    friend Vector2f& operator+(Vector2f& vec1, const Vector2f& vec2);
    friend Vector2f& operator-(Vector2f& vec1, const Vector2f& vec2);
    friend Vector2f& operator/(Vector2f& vec1, const Vector2f& vec2);
    friend Vector2f& operator*(Vector2f& vec1, const Vector2f& vec2);
    friend Vector2f& operator/(Vector2f& vec1, const float& val);
    friend Vector2f& operator*(Vector2f& vec1, const float& val);
    friend std::ostream& operator<<(std::ostream& out, const Vector2f& vec);

    Vector2f& operator+=(const Vector2f& vec);
    Vector2f& operator-=(const Vector2f& vec);
    Vector2f& operator/=(const Vector2f& vec);
    Vector2f& operator*=(const Vector2f& vec);

    // Scalar operations
    Vector2f& operator/=(const float& val);
    Vector2f& operator*=(const float& val);

    float magnitudeSqrt() const;
    float magnitude() const;
    Vector2f normalize();
};

#endif
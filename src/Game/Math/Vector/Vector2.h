#pragma once
#include <cmath>

//Vector2 for  2d positioning etc
struct Vector2
{
    float x = 0.0f;
    float y = 0.0f;

    // Constructors
    Vector2() = default;
    Vector2(float newX, float newY) : x(newX), y(newY) {}

    // Length (magnitude)
    float Length() const
    {
        return sqrt(x * x + y * y);
    }

    // Normalized Vector2
    Vector2 Normalize() const
    {
        float mag = Length();
        if (mag == 0.0f) return Vector2(0, 0);
        return Vector2(x / mag, y / mag);
    }

    // Distance to another vector
    float Distance(const Vector2& to) const
    {
        float dx = to.x - x;
        float dy = to.y - y;
        return sqrt(dx * dx + dy * dy);
    }

    // Direction TO another vector (normalized)
    Vector2 DirectionTo(const Vector2& to) const
    {
        return Vector2(to.x - x, to.y - y).Normalize();
    }

    // Dot product
    float Dot(const Vector2& other) const
    {
        return x * other.x + y * other.y;
    }    

    // Operators with Vector as Param
    Vector2 operator+(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }
    Vector2 operator-(const Vector2& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }
    Vector2 operator*(const Vector2& other) const
    {
        return Vector2(x * other.x, y * other.y);
    }
    Vector2 operator/(const Vector2& other) const
    {
        return Vector2(x / other.x, y / other.y);
    }       
 
    Vector2& operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // Operators with float as Param
    Vector2 operator+(const float value) const
    {
        return Vector2(x + value, y + value);
    }   
    Vector2 operator-(const float value) const
    {
        return Vector2(x - value, y - value);
    }

    Vector2 operator*(float scalar) const
    {
        return Vector2(x * scalar, y * scalar);
    }
    Vector2 operator/(float scalar) const
    {
        if (scalar > 0) return Vector2(x / scalar, y / scalar);
        else return Vector2(0, 0);
    }

    float Vector2::LengthSquared() const
    {
        return x * x + y * y;
    }
   
};





// Vector3 for 3D positioning, directions, physics, etc
struct Vector3
{
    float X = 0.0f;
    float Y = 0.0f;
    float Z = 0.0f;

    // Constructors
    Vector3() = default;
    Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

    // Length (magnitude)
    float Length() const
    {
        return std::sqrt(X * X + Y * Y + Z * Z);
    }

    // Normalized
    Vector3 Normalized() const
    {
        float Magnitude = Length();
        if (Magnitude == 0.0f) return Vector3(0, 0, 0);

        return Vector3(X / Magnitude, Y / Magnitude, Z / Magnitude);
    }

    // Distance to another vector
    float Distance(const Vector3& to) const
    {
        float dx = to.X - X;
        float dy = to.Y - Y;
        float dz = to.Z - Z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

    // Direction to another vector (normalized)
    Vector3 DirectionTo(const Vector3& to) const
    {
        return Vector3(to.X - X, to.Y - Y, to.Z - Z).Normalized();
    }

    // Dot product
    float Dot(const Vector3& other) const
    {
        return (X * other.X) + (Y * other.Y) + (Z * other.Z);
    }

    // Cross product
    Vector3 Cross(const Vector3& other) const
    {
        return Vector3( Y * other.Z - Z * other.Y, Z * other.X - X * other.Z,X * other.Y - Y * other.X);
    }

    // Operators
    Vector3 operator+(const Vector3& other) const
    {
        return Vector3(X + other.X, Y + other.Y, Z + other.Z);
    }

    Vector3 operator-(const Vector3& other) const
    {
        return Vector3(X - other.X, Y - other.Y, Z - other.Z);
    }

    Vector3 operator*(float scalar) const
    {
        return Vector3(X * scalar, Y * scalar, Z * scalar);
    }
};

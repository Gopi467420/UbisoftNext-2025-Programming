#include "Matrix.h"
#include "../Game/math/Vector/Vector2.h"
#include <cmath>


Matrix3x3::Matrix3x3() 
{
    // Initialize as identity Matrix
    for (int i = 0; i < 9; i++){ m[i] = 0.0f; }
    m[0] = 1.0f; m[4] = 1.0f; m[8] = 1.0f;
}


float& Matrix3x3::operator()(int row, int col) 
{
    return m[row + 3 * col]; 
}

const float& Matrix3x3::operator()(int row, int col) const 
{
    return m[row + 3 * col];
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other) const 
{
    Matrix3x3 result;
    for (int row = 0; row < 3; row++) 
    {
        for (int col = 0; col < 3; col++) 
        {
            result(row, col) = m[row + 0] * other.m[col * 3 + 0] +
                m[row + 3] * other.m[col * 3 + 1] +
                m[row + 6] * other.m[col * 3 + 2];
        }
    }
    return result;
}

Vector2 Matrix3x3::operator*(const Vector2& v) const 
{
    Vector2 result;
    result.x = m[0] * v.x + m[1] * v.y + m[2]; 
    result.y = m[3] * v.x + m[4] * v.y + m[5];
    return result;
}

Matrix3x3 Matrix3x3::Transpose() const 
{
    Matrix3x3 result;
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++) { result(row, col) = (*this)(col, row); }

    }
        
    return result;
}

Matrix3x3 Matrix3x3::Identity() 
{
    return Matrix3x3();
}

Matrix3x3 Matrix3x3::Translate(const Vector2& v) 
{
    Matrix3x3 mat = Identity();
    mat(0, 2) = v.x;
    mat(1, 2) = v.y;
    return mat;
}

Matrix3x3 Matrix3x3::Scale(const Vector2& v) 
{
    Matrix3x3 mat = Identity();
    mat(0, 0) = v.x;
    mat(1, 1) = v.y;
    return mat;
}

Matrix3x3 Matrix3x3::Rotate(float angleinDegrees) 
{
    Matrix3x3 mat = Identity();
    float rad = angleinDegrees * 3.14159265f / 180.0f;
    float c = cosf(rad);
    float s = sinf(rad);
    mat(0, 0) = c;  mat(0, 1) = -s;
    mat(1, 0) = s;  mat(1, 1) = c;
    return mat;
}

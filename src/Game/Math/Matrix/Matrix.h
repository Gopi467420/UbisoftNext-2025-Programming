#pragma once


struct Vector2;

struct Matrix3x3 
{
public:
    // Constructor
    Matrix3x3();

private:
    float m[9]; 

public:

    //Get Elements at (row, col)
    float& operator()(int row, int col);
    const float& operator()(int row, int col) const;
  

    // Matrix multiplication
    Matrix3x3 operator*(const Matrix3x3& other) const;
   

    // Apply matrix to a Vector2
    Vector2 operator*(const Vector2& v) const;

    // Transpose matrix
    Matrix3x3 Transpose() const;



    // Static helper functions
    static Matrix3x3 Identity();
    static Matrix3x3 Translate(const Vector2& v);
    static Matrix3x3 Scale(const Vector2& v);
    static Matrix3x3 Rotate(float angleinDegrees);
};

